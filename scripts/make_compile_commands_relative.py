#!/usr/bin/env python3
"""
Rewrite compile_commands.json so it uses relative paths to the workspace.

This helps tools like Trunk create temporary workspaces and keep ``include/`` paths resolvable
when they copy the project into `/tmp/` or other temp directories.

It converts absolute `directory`, `file` and `command` fields using the
`GITHUB_WORKSPACE` environment variable if present; otherwise, it falls back to
the current working directory.
"""
from __future__ import annotations
import json
import os
import sys
from pathlib import Path


def main() -> int:
    repo_root = os.environ.get("GITHUB_WORKSPACE") or os.getcwd()
    gw_path = os.path.abspath(repo_root)
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
        if entry.get("directory"):
            d = os.path.abspath(entry["directory"])
            if d.startswith(gw_path):
                entry["directory"] = "." + d[len(gw_path):]
        if entry.get("file"):
            fpath = os.path.abspath(entry["file"])
            if fpath.startswith(gw_path + os.sep):
                entry["file"] = "." + fpath[len(gw_path):]
        if entry.get("command"):
            entry["command"] = entry["command"].replace(gw_path + os.sep, "./")

    with cc_path.open("w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)

    print("Rewrote compile_commands.json paths to relative")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
