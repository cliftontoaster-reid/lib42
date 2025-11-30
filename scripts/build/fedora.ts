import { Platform, PlatformOptions } from "./pack.ts";

const neededCommands = ["rpmbuild", "tar"];

const treeDirs = ["BUILD", "BUILDROOT", "RPMS", "SOURCES", "SPECS", "SRPMS"];

export class FedoraPlatform extends Platform {
  private rpmBuildDir?: string;

  constructor(opts?: PlatformOptions) {
    super("fedora", "rpm", opts);
  }

  override async prepare(): Promise<void> {
    for (const cmd of neededCommands) {
      const command = new Deno.Command("which", {
        args: [cmd],
      });

      const { success } = await command.output();

      if (!success) {
        throw new Error(`Required command not found: ${cmd}`);
      }
    }

    // Create an RPM build tree in a temporary directory so we don't pollute
    // the workspace. rpmbuild requires an absolute topdir, so create a
    // temp directory and use that as rpmbuild's topdir.
    const name = this.opts.name ?? "lib42";
    this.opts.buildDir = await Deno.makeTempDir({
      prefix: `${name}-rpmbuild-`,
    });
    const rpmBuildDir = Deno.realPathSync(this.opts.buildDir);
    // Store the temp RPM build dir so we can clean it up later
    this.rpmBuildDir = rpmBuildDir;

    // We do not build here: rpmbuild will run the build inside its own
    // temporary build root (via %cmake / %cmake_build). Do not set
    // `opts.buildDir` because the spec uses rpmbuild macros to construct
    // the build path which must not include extra quoting.

    for (const dir of treeDirs) {
      Deno.mkdirSync(`${rpmBuildDir}/${dir}`, { recursive: true });
    }

    return Promise.resolve();
  }

  override build(): Promise<void> {
    /// RPM build is handled by rpmbuild command later
    return Promise.resolve();
  }

  override async package(): Promise<string> {
    const outDir = this.opts.outDir ?? "dist";
    const rpmBuildDir =
      this.rpmBuildDir ?? Deno.realPathSync(`${outDir}/${this.ext}`);
    const srcDir = this.opts.srcDir ?? ".";

    // Extract version from top-level CMakeLists.txt
    const cmakeFile = `${srcDir}/CMakeLists.txt`;
    const cmakeText = await Deno.readTextFile(cmakeFile);
    const getVal = (name: string) => {
      const m = cmakeText.match(
        new RegExp(`set\\(\\s*${name}\\s+([^\\)]+)\\s*\\)`, "m"),
      );
      return m ? m[1].trim() : undefined;
    };

    const major = getVal("PROJECT_VERSION_MAJOR") ?? "0";
    const minor = getVal("PROJECT_VERSION_MINOR") ?? "0";
    const patch = getVal("PROJECT_VERSION_PATCH") ?? "0";
    const version = `${major}.${minor}.${patch}`;

    const name = this.opts.name ?? "lib42";

    // Create a source tarball that rpmbuild will consume
    const tarName = `${name}-${version}.tar.gz`;
    const tarPath = `${rpmBuildDir}/SOURCES/${tarName}`;

    // Exclude the packaging output tree to avoid tar reading new files while creating archive
    const tarCmd = new Deno.Command("tar", {
      args: [
        "-czf",
        tarPath,
        "--exclude",
        outDir,
        "--owner=0",
        "--group=0",
        "--transform",
        `s,^,${name}-${version}/,`,
        "-C",
        srcDir,
        ".",
      ],
    });
    const tarProc = tarCmd.spawn();
    const tarStatus = await tarProc.status;
    if (!tarStatus.success) {
      throw new Error("tar failed while creating source archive");
    }

    // Replace version placeholders in the spec file and write it into SPECS
    const specSrc = await Deno.readTextFile(`${srcDir}/docs/fedora.spec`);
    let specRendered = specSrc
      .replace(/@PROJECT_VERSION_MAJOR@/g, major)
      .replace(/@PROJECT_VERSION_MINOR@/g, minor)
      .replace(/@PROJECT_VERSION_PATCH@/g, patch);

    // If there is a prerelease token, replace, otherwise remove the token placeholder
    const pre = getVal("PROJECT_VERSION_PRERELEASE");
    if (pre) {
      specRendered = specRendered.replace(/@PROJECT_VERSION_PRERELEASE@/g, pre);
    } else {
      specRendered = specRendered.replace(/@PROJECT_VERSION_PRERELEASE@/g, "");
    }

    const specPath = `${rpmBuildDir}/SPECS/${name}.spec`;
    await Deno.writeTextFile(specPath, specRendered);

    // Run rpmbuild to create RPMs
    const rpmbuild = new Deno.Command("rpmbuild", {
      args: ["-ba", "--define", `_topdir ${rpmBuildDir}`, specPath],
    });
    const rpmbuildProc = rpmbuild.spawn();
    const rbStatus = await rpmbuildProc.status;
    if (!rbStatus.success) {
      throw new Error("rpmbuild failed");
    }

    return `${rpmBuildDir}/RPMS`;
  }

  /**
   * Remove this platform's temporary rpm build directory if present.
   */
  override cleanup(): Promise<void> {
    // Remove the temporary RPM build tree if we created one
    if (this.rpmBuildDir) {
      try {
        console.info(`Removing temporary RPM build dir: ${this.rpmBuildDir}`);
        Deno.removeSync(this.rpmBuildDir, { recursive: true });
        console.info("Removal complete.");
      } catch {
        console.warn(
          `Failed to remove temporary RPM build dir: ${this.rpmBuildDir}`,
        );
      }
    }

    // Remove the CMake build dir if used
    return super.cleanup();
  }
}
