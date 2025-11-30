import { Platform, PlatformOptions } from "./pack.ts";

const neededCommands = ["dpkg-deb", "tar", "dpkg"];

export class DebianPlatform extends Platform {
  private stagingDir?: string;

  constructor(opts?: PlatformOptions) {
    super("debian", "deb", opts);
  }

  override async prepare(): Promise<void> {
    for (const cmd of neededCommands) {
      const command = new Deno.Command("which", { args: [cmd] });
      const { success } = await command.output();

      if (!success) {
        throw new Error(`Required command not found: ${cmd}`);
      }
    }

    // Put the CMake build in a temporary directory so packaging does not
    // pollute the working tree.
    const name = this.opts.name ?? "lib42";
    this.opts.buildDir = await Deno.makeTempDir({
      prefix: `${name}-deb-build-`,
    });

    // staging dir for dpkg-deb packaging
    this.stagingDir = await Deno.makeTempDir({
      prefix: `${name}-deb-staging-`,
    });

    return Promise.resolve();
  }

  override async package(): Promise<string> {
    const outDir = this.opts.outDir ?? "dist";
    const srcDir = this.opts.srcDir ?? ".";
    const stagingDir = this.stagingDir!;

    // Build was done already; run cmake --install to populate a faux /usr
    // tree inside the staging directory.
    const buildDir = this.opts.buildDir ?? "build";

    const cmInstall = new Deno.Command("cmake", {
      args: ["--install", buildDir, "--prefix", `${stagingDir}/usr`],
    });
    const cmInstallProc = cmInstall.spawn();
    const cmInstallStatus = await cmInstallProc.status;
    if (!cmInstallStatus.success) {
      throw new Error("cmake --install failed while staging package");
    }

    // Read version from CMakeLists
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

    // Render control template from docs
    const controlSrc = await Deno.readTextFile(`${srcDir}/docs/debian.control`);

    const dpkgPrintArch = new Deno.Command("dpkg", {
      args: ["--print-architecture"],
    });
    const archOut = await dpkgPrintArch.output();
    const arch = archOut.success
      ? new TextDecoder().decode(archOut.stdout).trim()
      : "all";

    // If there is a prerelease token, use Debian's ~ syntax to ensure
    // versions compare as expected (1.0.0~alpha). Otherwise use empty string.
    const pre = getVal("PROJECT_VERSION_PRERELEASE");
    const prereleaseStr = pre ? `~${pre}` : "";

    const controlRendered = controlSrc
      .replace(/@PROJECT_VERSION_MAJOR@/g, major)
      .replace(/@PROJECT_VERSION_MINOR@/g, minor)
      .replace(/@PROJECT_VERSION_PATCH@/g, patch)
      .replace(/@PROJECT_VERSION_PRERELEASE@/g, prereleaseStr)
      .replace(/@ARCH@/g, arch);

    await Deno.mkdir(`${stagingDir}/DEBIAN`);
    await Deno.writeTextFile(`${stagingDir}/DEBIAN/control`, controlRendered);

    // Build .deb using dpkg-deb
    const pkgOutDir = `${outDir}/${this.ext}`;
    await Deno.mkdir(pkgOutDir, { recursive: true });

    const debName = `${name}_${version}_${arch}.${this.ext}`;
    const debOut = `${pkgOutDir}/${debName}`;

    // If we're not root, dpkg-deb suggests using --root-owner-group for
    // rootless builds. Use the environment's UID when available; otherwise
    // run `id -u` to detect. See: https://wiki.debian.org/Teams/Dpkg/RootlessBuilds
    let isRoot = false;
    try {
      const uidEnv = Deno.env.get("UID");
      if (uidEnv !== undefined) {
        isRoot = uidEnv === "0";
      } else {
        const idCmd = new Deno.Command("id", { args: ["-u"] });
        const idOut = await idCmd.output();
        if (idOut.success) {
          const uidStr = new TextDecoder().decode(idOut.stdout).trim();
          isRoot = uidStr === "0";
        }
      }
    } catch {
      // If we can't detect the uid (command missing or permission denied),
      // default to not root so we produce a dpkg-friendly package for
      // non-root environments by passing --root-owner-group.
      isRoot = false;
    }

    const dpkgArgs = ["-b"] as string[];
    if (!isRoot) {
      // Some older dpkg-deb versions may not support this flag; check
      // before adding it to the args so we remain compatible.
      try {
        const helpOut = await new Deno.Command("dpkg-deb", {
          args: ["--help"],
        }).output();
        const helpText = new TextDecoder().decode(helpOut.stdout);
        if (helpOut.success && helpText.includes("--root-owner-group")) {
          dpkgArgs.push("--root-owner-group");
        }
      } catch {
        // If help failed for any reason, skip adding the flag.
      }
    }
    dpkgArgs.push(stagingDir, debOut);

    const dpkgDeb = new Deno.Command("dpkg-deb", {
      args: dpkgArgs,
    });
    const dpkgDebProc = dpkgDeb.spawn();
    const dpkgStatus = await dpkgDebProc.status;
    if (!dpkgStatus.success) {
      throw new Error("dpkg-deb failed while creating package");
    }

    return `${pkgOutDir}/${debName}`;
  }

  override cleanup(): Promise<void> {
    // Remove the temporary staging directory used by deb packaging
    if (this.stagingDir) {
      try {
        Deno.removeSync(this.stagingDir, { recursive: true });
      } catch {
        // ignore
      }
    }

    return super.cleanup();
  }
}
