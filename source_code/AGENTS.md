# Desktop app source (source_code/)

## Purpose

Partial C++ source of the File Centipede desktop application: `fileu/` (Qt Widgets main app) and `fileu_launch/` (launcher helper). This copy is incomplete — the full upstream project lives in the filecxx/FileCentipede GitHub repository.

## Ownership

- Owns: C++ source organization of the files present here
- Does not own: built binaries (`../release/`), UI strings (`../lang/software/`)

## Local Contracts

- Build system: CMake + Qt 5.15.2 with `CMAKE_AUTOMOC`. `fileu/CMakeLists.txt` includes `../CMakeHeader.txt`, which is not present in this workspace — this copy does not build as-is
- CMakeLists hardcode machine-specific Qt paths (Windows `I:\Librarys\Qt\...`, Linux `/opt/Qt5`); adjust when building
- User-visible strings are not compiled in: `main_window.cpp` loads `.lang` files from a workspace `lang/` directory at runtime with `en_US` fallback, sourced from `../lang/software/`
- `fileu/` module map: `catalogs/`, `dialogs/`, `file_browser/`, `file_manager/`, `help/`, `plugins/`, `search_engine/`, `settings/`, `tasks/`, `tools/`, `view/` — one feature per folder; root files are `main.cpp`, `main_window.*`, and `pro_*` (globals, headers, methods)
- `fileu_launch/`: minimal launcher (`main.cpp`, CMakeLists, Win32 resources)

## Work Guidance

- Follow existing conventions: snake_case file names, `<module>_<topic>.(cpp|h)` pairs per class, Qt Widgets idioms
- Do not hardcode user-visible strings; keep them resolvable via the runtime `.lang` mechanism

## Verification

None available — the missing `CMakeHeader.txt` means no build or test framework runs against this copy.

## Child DOX Index

None — leaf scope.
