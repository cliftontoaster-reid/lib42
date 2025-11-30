#!/usr/bin/env python3
"""
Rewrite compile_commands.json so it uses absolute paths.

Tools like Trunk require absolute paths in compile_commands.json.
CMake sometimes generates relative paths (e.g., "./src/...", "-I./include")
which cause errors like "AbsolutePath can not be constructed with a relative path".

This script converts relative paths to absolute paths. Relative paths like
"./src" or "./include" are resolved relative to the workspace root (not the
build directory), since CMake typically generates these paths relative to
where the source files are located.
"""
from __future__ import annotations
import json
import os
import re
import sys
from pathlib import Path


def make_absolute(path: str, base_dir: str) -> str:
    """Convert a path to absolute if it's relative."""
    if os.path.isabs(path):
        return path
    return os.path.normpath(os.path.join(base_dir, path))


def fix_command(command: str, repo_root: str) -> str:
    """Fix relative paths in compiler command strings.

    Relative paths like "./include" or "./src/..." are resolved relative
    to the repo root, not the build directory.
    """
    # Fix -I"./path" or -I./path patterns
    def replace_include(match: re.Match) -> str:
        prefix = match.group(1)  # -I or -I"
        path = match.group(2)
        suffix = match.group(3)  # optional closing quote
        if path.startswith("./") or path.startswith("../"):
            abs_path = make_absolute(path, repo_root)
            return f'{prefix}{abs_path}{suffix}'
        return match.group(0)

    # Match -I"./path" or -I./path patterns
    command = re.sub(r'(-I"?)(\./[^"\s]+|\.\.\/[^"\s]+)("?)', replace_include, command)

    # Fix -c "./path" patterns (source files)
    def replace_source(match: re.Match) -> str:
        prefix = match.group(1)  # -c or -c "
        path = match.group(2)
        suffix = match.group(3)  # optional closing quote
        if path.startswith("./") or path.startswith("../"):
            abs_path = make_absolute(path, repo_root)
            return f'{prefix}{abs_path}{suffix}'
        return match.group(0)

    command = re.sub(r'(-c\s+"?)(\./[^"\s]+|\.\.\/[^"\s]+)("?)', replace_source, command)

    return command


def main() -> int:
    repo_root = os.environ.get("GITHUB_WORKSPACE") or os.getcwd()
    repo_root = os.path.abspath(repo_root)
    cc_path = Path("compile_commands.json")
    if not cc_path.exists():
        print("compile_commands.json not found; nothing to do.")
        return 0

    with cc_path.open("r", encoding="utf-8") as f:
        try:
            data = json.load(f)
        except Exception as e:
            print(f"Failed to parse compile_commands.json: {e}")
            return 2

    for entry in data:
        # Make directory absolute (relative to repo root)
        if entry.get("directory"):
            entry["directory"] = make_absolute(entry["directory"], repo_root)

        # Make file path absolute (relative to repo root, not build dir)
        # Paths like "./src/..." should resolve to repo_root/src/...
        if entry.get("file"):
            entry["file"] = make_absolute(entry["file"], repo_root)

        # Fix paths in command (relative to repo root)
        if entry.get("command"):
            entry["command"] = fix_command(entry["command"], repo_root)

    with cc_path.open("w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)

    print("Rewrote compile_commands.json paths to absolute")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
