// Lightweight packaging framework for Deno
// Provides an abstract Platform base class with lifecycle hooks
// and simple concrete implementations for demonstration.

export type PlatformOptions = {
  srcDir?: string; // where the built artifacts are
  outDir?: string; // where packages should be written
  name?: string; // package name
  version?: string; // package version
  buildDir?: string; // optional custom build directory
};

export abstract class Platform {
  name: string;
  ext: string;
  opts: PlatformOptions;

  constructor(name: string, ext: string, opts?: PlatformOptions) {
    this.name = name;
    this.ext = ext;
    this.opts = opts ?? {};
  }

  cleanup(): Promise<void> {
    // Delete build directory if it exists
    const buildDir = this.opts.buildDir ?? `./build`;
    try {
      Deno.removeSync(buildDir, { recursive: true });
    } catch {
      // Ignore errors if the directory does not exist
    }
    return Promise.resolve();
  }

  abstract prepare(): Promise<void>;

  async build(): Promise<void> {
    // Run cmake
    const buildDir = this.opts.buildDir ?? "build";

    const cmake = new Deno.Command("cmake", {
      args: [
        "-S",
        this.opts.srcDir ?? ".",
        "-B",
        buildDir,
        "-DCMAKE_BUILD_TYPE=Release",
        "-DBUILD_TESTING=OFF",
      ],
    });

    const cmakeChild = cmake.spawn();
    const cmakeStatus = await cmakeChild.status;
    if (!cmakeStatus.success) {
      throw new Error("CMake configuration failed");
    }

    // Run build
    const build = new Deno.Command("cmake", {
      args: ["--build", buildDir, "--config", "Release"],
    });

    const buildChild = build.spawn();
    const buildStatus = await buildChild.status;
    if (!buildStatus.success) {
      throw new Error("Build failed");
    }

    return Promise.resolve();
  }

  abstract package(): Promise<string>;

  async run(): Promise<string> {
    console.info(`Starting packaging for platform: ${this.name}`);
    await this.prepare();
    console.info("Preparation complete.");
    console.info("Starting build...");
    await this.build();
    console.info("Build complete.");
    console.info("Starting packaging...");
    return this.package();
  }
}
