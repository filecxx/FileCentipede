#!/usr/bin/env python3
"""Verify software translation catalogs against en_US.lang."""

from pathlib import Path
import sys


CATALOG_DIR = Path(__file__).resolve().parent.parent
SOURCE = CATALOG_DIR / "en_US.lang"


def read_keys(path: Path) -> list[str]:
    keys = []
    with path.open(encoding="utf-8", newline=None) as catalog:
        for line_number, line in enumerate(catalog, start=1):
            entry = line.rstrip("\r\n")
            if "=" not in entry:
                raise ValueError(f"{path.name}:{line_number}: expected key=value entry")
            keys.append(entry.split("=", 1)[0])
    return keys


def main() -> int:
    try:
        source_keys = read_keys(SOURCE)
    except (OSError, UnicodeError, ValueError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        return 1

    failed = False
    for path in sorted(CATALOG_DIR.glob("*.lang")):
        if path == SOURCE:
            continue
        try:
            keys = read_keys(path)
        except (OSError, UnicodeError, ValueError) as error:
            print(f"FAIL {path.name}: {error}")
            failed = True
            continue

        missing = [key for key in source_keys if key not in keys]
        extra = [key for key in keys if key not in source_keys]
        issues = []
        if missing or extra:
            issues.append(f"key set differs (missing={len(missing)}, extra={len(extra)})")
        if keys != source_keys:
            issues.append("key order differs")
        if len(keys) != len(source_keys):
            issues.append(f"key count differs ({len(keys)} != {len(source_keys)})")

        if issues:
            print(f"FAIL {path.name}: {'; '.join(issues)}")
            failed = True
        else:
            print(f"PASS {path.name}: {len(keys)} keys")

    if failed:
        return 1
    print(f"PASS: all translation catalogs match en_US.lang ({len(source_keys)} keys)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
