#!/usr/bin/env -S deno run --allow-read --allow-write --allow-net --allow-env --allow-run

import { FedoraPlatform } from "./build/fedora.ts";
import { DebianPlatform } from "./build/debian.ts";

const supportedPackages = [
  ["debian", "deb"],
  ["fedora", "rpm"],
];

const buildDir = "./dist";

FedoraPlatform;

async function runPlatformPackage(platformId: string): Promise<void> {
  switch (platformId) {
    case "debian": {
      const platform = new DebianPlatform({ outDir: buildDir });
      const packagePath = await platform.run();
      console.info(`Package created at: ${packagePath}`);
      try {
        await Deno.mkdir(buildDir, { recursive: true });
      } catch {
        // ignore if exists
      }
      await platform.cleanup();
      break;
    }
    case "fedora": {
      const platform = new FedoraPlatform({ outDir: buildDir });
      const packagePath = await platform.run();
      console.info(`Package created at: ${packagePath}`);
      try {
        await Deno.mkdir(buildDir, { recursive: true });
      } catch {
        // ignore if exists
      }
      await Deno.mkdir(`${buildDir}/rpm`, { recursive: true });
      for await (const archEntry of Deno.readDir(packagePath)) {
        const archPath = `${packagePath}/${archEntry.name}`;

        if (archEntry.isDirectory) {
          for await (const fileEntry of Deno.readDir(archPath)) {
            if (!fileEntry.isFile) continue;
            const srcPath = `${archPath}/${fileEntry.name}`;
            const destPath = `${buildDir}/rpm/${fileEntry.name}`;
            await Deno.copyFile(srcPath, destPath);
          }
        } else if (archEntry.isFile) {
          // Some platforms may place files directly in the output dir
          const srcPath = archPath;
          const destPath = `${buildDir}/rpm/${archEntry.name}`;
          await Deno.copyFile(srcPath, destPath);
        }
      }
      await platform.cleanup();
      break;
    }
    default:
      console.error(`Unsupported platform: ${platformId}`);
      Deno.exit(1);
  }
}

async function main() {
  const args = Deno.args;
  if (args.length === 0) {
    console.error(
      `Usage: ${Deno.mainModule} <platform>\nSupported platforms: ${supportedPackages
        .map((p) => p[0])
        .join(", ")}`,
    );
    Deno.exit(1);
  }

  // First we filter out unsupported platforms
  for (const platformId of args) {
    const isSupported = supportedPackages.some((p) => p[0] === platformId);
    if (!isSupported) {
      console.error(`Unsupported platform: ${platformId}`);
      Deno.exit(1);
    }
  }

  // Now we can run packaging for each requested platform
  for (const platformId of args) {
    console.info(`Packaging for platform: ${platformId}`);
    await runPlatformPackage(platformId);
  }
}

await main();
