# Translation sources (lang/)

## Purpose

The only place translated strings live. Three channels feed three consumers: the website (`../tpl/` pages), the desktop software (loaded at runtime), and the browser extension.

## Ownership

- Owns: key sets, translation content, and locale coverage for all three channels
- Does not own: where keys are consumed — website layout in `../tpl/`, software UI in `../source_code/fileu/`, extension code (not in this repo)

## Local Contracts

Formats and locale naming differ per channel:

- `website/` — key=value `.lang` files for the website, referenced by `../tpl/` as `${key}`. Root files (`en_US.lang`, `zh_CN.lang`, `zh_TW.lang`, `ru_RU.lang`, `ko_KR.lang`, `de_DE.lang`, `id_ID.lang`, `tr_TR.lang`) hold site-wide keys; `documentation/`, `features/`, `os/` hold per-page key sets and exist only for pages translated so far. `en_US` is the reference set.
- `software/` — key=value `.lang` files for the desktop app, 16 locales (e.g. `en_US`, `zh_CN`, `de_DE`, `ja_JP`, `vi_VN`). The app loads them at runtime with `en_US` fallback.
- `browser_extension/<locale>/messages.json` — Chrome `_locales` format, 9 locales with irregular naming: `en`, `id`, `ja`, `ko`, `tr`, `zh_CN`, `zh_TW`, `de_DE`, `pl_PL`.
- File format: `key=value`, one per line; values may be quoted and span multiple lines; keys ending in `_` may contain HTML (`<br/>`, links)

## Work Guidance

- Adding a website string: add the key to `website/en_US.lang` (or the page's `en_US.lang`) and use it as `${key}` in `../tpl/`; add other locales as available
- Key names are contracts with consumers — never rename a key without updating every locale file of that channel and the consuming pages/source
- Match each channel's locale naming exactly (see Local Contracts); do not normalize across channels

## Verification

No automated framework exists. Useful manual checks:

- Key coverage: compare key counts/sets between a locale file and its channel's `en_US` reference (e.g. `grep -c '=' de_DE.lang` vs `en_US.lang`)
- Website keys: confirm keys added here appear as `${key}` in `../tpl/` and vice versa

## Child DOX Index

None — leaf scope.
