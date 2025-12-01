import { Platform, PlatformOptions } from "./pack.ts";

export class ArchPlatform extends Platform {
  constructor(opts?: PlatformOptions) {
    super("arch", "pkg.tar.zst", opts);
  }

  override prepare(): Promise<void> {
    // No special preparation needed for AUR - we just generate files
    return Promise.resolve();
  }

  override build(): Promise<void> {
    // AUR packages are built by the user via makepkg, not by us
    return Promise.resolve();
  }

  override async package(): Promise<string> {
    const outDir = this.opts.outDir ?? "dist";
    const srcDir = this.opts.srcDir ?? ".";
    const aurDir = `${outDir}/arch`;

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
    const pre = getVal("PROJECT_VERSION_PRERELEASE");

    // Create output directory
    await Deno.mkdir(aurDir, { recursive: true });

    // Read and render PKGBUILD template
    const pkgbuildSrc = await Deno.readTextFile(`${srcDir}/docs/PKGBUILD`);
    let pkgbuildRendered = pkgbuildSrc
      .replace(/@PROJECT_VERSION_MAJOR@/g, major)
      .replace(/@PROJECT_VERSION_MINOR@/g, minor)
      .replace(/@PROJECT_VERSION_PATCH@/g, patch);

    // Handle prerelease: Arch uses _ for pre-release versions
    if (pre) {
      pkgbuildRendered = pkgbuildRendered.replace(
        /@PROJECT_VERSION_PRERELEASE@/g,
        `_${pre.replace(/\./g, "_")}`,
      );
    } else {
      pkgbuildRendered = pkgbuildRendered.replace(
        /@PROJECT_VERSION_PRERELEASE@/g,
        "",
      );
    }

    await Deno.writeTextFile(`${aurDir}/PKGBUILD`, pkgbuildRendered);

    // Copy .SRCINFO if it exists, otherwise generate a basic one
    try {
      const srcinfoSrc = await Deno.readTextFile(`${srcDir}/docs/.SRCINFO`);
      let srcinfoRendered = srcinfoSrc
        .replace(/@PROJECT_VERSION_MAJOR@/g, major)
        .replace(/@PROJECT_VERSION_MINOR@/g, minor)
        .replace(/@PROJECT_VERSION_PATCH@/g, patch);

      if (pre) {
        srcinfoRendered = srcinfoRendered.replace(
          /@PROJECT_VERSION_PRERELEASE@/g,
          `_${pre.replace(/\./g, "_")}`,
        );
      } else {
        srcinfoRendered = srcinfoRendered.replace(
          /@PROJECT_VERSION_PRERELEASE@/g,
          "",
        );
      }

      await Deno.writeTextFile(`${aurDir}/.SRCINFO`, srcinfoRendered);
    } catch {
      // .SRCINFO template doesn't exist, that's fine
      // Users can generate it with `makepkg --printsrcinfo > .SRCINFO`
      console.info(
        "Note: .SRCINFO template not found. Generate with: makepkg --printsrcinfo > .SRCINFO",
      );
    }

    return aurDir;
  }

  override cleanup(): Promise<void> {
    // Nothing to clean up for AUR - we don't create temporary directories
    return Promise.resolve();
  }
}
