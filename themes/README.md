# File Centipede — dark theme pack

A drop-in dark theme ("Matte Night" — flat, matte charcoal with a cyan-blue accent) for the
[File Centipede](https://github.com/filecxx/FileCentipede) desktop app, with a **Theme** toggle
button in the app's main toolbar that switches between dark and light.

The desktop app styles itself at runtime from plain files next to the executable —
`ui/css/default.css` (a Qt stylesheet) and the SVG icons in `icons/` — so a theme is just a
swappable set of those files. No rebuilding, no patching.

![dark](../images/screenshot_software.png)

## Install

1. Extract `release/filecxx_latest_win_x64.zip` (or use your installed portable copy) — you need
   the folder that contains `fileu.exe` and `ui/`
2. Copy this `themes/` folder and `theme_switch.bat` into that folder, next to `fileu.exe`
3. Start (or restart) the app — it boots in the currently selected theme; click **Theme** in the
   toolbar to switch

The first switch applies the theme toolbar button and restarts the app; each click toggles
dark ↔ light (the app restarts, tasks and catalogs are kept — they live outside the themed
files). A brief console window flash while the switch script runs is normal.

## What gets swapped

| Pack file | App location | Content |
|---|---|---|
| `dark/default.css`, `light/default.css` | `ui/css/default.css` | Qt stylesheet (colors, tabs, tables, dialogs) |
| `dark/css_images/`, `light/css_images/` | `ui/css/images/` | stylesheet-referenced images (tab close, expand/collapse) |
| `dark/icons/`, `light/icons/` | `icons/` | full icon tree — monochrome icons use light ink for dark UI, dark ink for light UI |
| `sml/` | `ui/` | UI markup overlay: adds the **Theme** toolbar button (`actions.sml`, `main.sml`) and dark-safe inline colors (`main_remote.sml`, `settings/main.sml`) |

`theme_switch.bat` applies the `sml/` overlay, copies the selected theme's files over the app's,
tracks the current theme with a `ui/css/theme_is_dark` marker, guards against duplicate triggers
with a 15-second lock, and restarts the app.

## Known limitations

- **Finished-task rows stay dark-on-dark in dark mode.** Task names and state labels are painted
  by the app's closed-source core with hardcoded light-theme ink (measured `rgb(31,31,31)` for
  completed rows); Qt stylesheets cannot override per-row colors set by the program. Everything
  the stylesheet controls — icons, headers, chrome, forms — is themed. Use light mode if you need
  those rows readable.
- The window title bar stays OS-styled; Qt stylesheets cannot reach it.
- Toggling restarts the app because the stylesheet is loaded once at startup.

## Customizing

Edit `dark/default.css` (the palette is at the top: base `#1b1e23`, surfaces `#212529`,
accent `#3daee9`), copy it into the app's `ui/css/default.css`, and restart. Icon ink for dark
mode is `rgb(170,178,187)` inside `dark/icons/**/*.svg`; colored icons (e.g. the red
`icons/24/failed.svg`) are intentionally left colored.

## Why this is a folder and not a patch

The upstream git repository ships neither `ui/` nor `icons/` — they exist only inside the
release archives — so the theme is distributed as a complete, self-contained overlay for an
extracted app folder. If you want native dark-mode support upstream, ask the maintainer to load
`ui/css/default.css` variants (e.g. an in-app theme switch) — the runtime theming layer already
supports it.
