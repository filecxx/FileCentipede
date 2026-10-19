# Dark theme pack (themes/)

## Purpose

Drop-in dark ("Matte Night") + light theme for the File Centipede desktop app with an in-app toolbar toggle. The app styles itself at runtime from `ui/css/default.css` (Qt stylesheet) and `icons/` SVGs inside an extracted release folder; this folder carries complete swappable file sets, a UI-markup overlay, and the toggle script. Distributed as an overlay because the upstream git repo ships neither `ui/` nor `icons/` — they exist only inside the release archives.

## Ownership

- Owns: theme file sets (`dark/`, `light/`), the `sml/` UI overlay, `theme_switch.bat`, theme docs (`README.md`)
- Does not own: app binaries (`../release/`), app source (`../source_code/`), website assets

## Local Contracts

- Layout mirrors the app runtime: `<theme>/default.css` → `ui/css/default.css`, `<theme>/css_images/` → `ui/css/images/`, `<theme>/icons/` → `icons/`
- `light/` is the pristine file set extracted from `release/filecxx_latest_win_x64.zip`; `dark/` is the Matte Night theme (base `#1b1e23`, accent `#3daee9`)
- `sml/` overlays `ui/` on every switch (both themes): `actions.sml` + `main.sml` add the `Action#act_theme_toggle` toolbar button (`trigger:$open-local-url("${__workspace__}theme_switch.bat")`), `main_remote.sml` + `settings/main.sml` carry dark-safe inline color fixes — without the overlay the button vanishes and dark mode shows unreadable hardcoded colors
- `theme_switch.bat` must run from inside an extracted app folder (next to `fileu.exe`, `themes/` beside it): toggles via presence of `ui/css/theme_is_dark`, holds a 15s lock (`%TEMP%\fc_theme.lock`) against duplicate triggers (the in-app click can fire twice), restarts the app
- Monochrome icon ink: `rgb(170,178,187)` under `dark/icons/`, original dark ink under `light/icons/`; colored icons (e.g. `24/failed.svg` red) stay colored in both

## Work Guidance

- Theme color changes go in `dark/default.css`; keep both theme sets in sync structurally (same file lists) or the toggle drifts
- Any change to the toggle flow or the `sml/` overlay requires a dark→light→dark round-trip retest in an extracted app folder before commit
- Task names/state labels are painted by the closed-source core with fixed light-theme ink — do not try to fix them in the css; it cannot override per-row program colors

## Verification

No automated framework. Manual: copy `themes/` + `theme_switch.bat` next to `fileu.exe` of a fresh `filecxx_latest_win_x64.zip` extraction, click **Theme** twice, confirm both renders (dark: light-ink sidebar icons, readable headers; light: original look, Theme button still present), and `ui/css/theme_is_dark` flips.

## Child DOX Index

None — leaf scope.
