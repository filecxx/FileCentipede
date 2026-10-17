# Website template (tpl/)

## Purpose

Master template of the filecxx.com static website. `tpl/` is the single source of truth for site pages, structure, and layout. A site generator renders the locale websites (`../de_DE/`, `../en_US/`, `../id_ID/`, `../ko_KR/`, `../ru_RU/`, `../tr_TR/`, `../zh_CN/`, `../zh_TW/`) from it; the generator itself is not part of this workspace.

## Ownership

- Owns: page structure, layout, navigation, partials, and placeholder placement
- Does not own: translated strings (`../lang/website/`), generated locale pages, shared assets (`../style/`, `../script/`, `../images/`)

## Local Contracts

- `${key}` placeholders are filled from `../lang/website/<locale>.lang` merged with the matching per-page file under `../lang/website/{documentation,features,os}/<page>/<locale>.lang`; per-page folders exist only for pages translated so far
- `${@import tpl/<file>.html}` pulls in partials; the `tpl_*.html` files are those partials (htmlmeta, nav, nav_root, header, download, footer, share, analysis)
- The directory layout mirrors 1:1 into every locale folder: root pages plus `documentation/`, `external_links/`, `feature_showcase/`, `features/`, `os/`, `tpl/`
- Shared assets are referenced relative to the repo root: `../style/`, `../script/`, `../images/`, `../favicon.ico`
- Inline `<script>` blocks inside pages are part of the template and must stay locale-independent

## Work Guidance

- Add or change site content/structure in `tpl/` and add new keys to `../lang/website/en_US.lang` (plus the page's per-page `.lang` for page-specific keys); locale folders are regenerated output — never hand-edit them
- Keep visible copy in `tpl/` as `${key}` placeholders so translations stay in `lang/`; hardcode only locale-independent markup
- The language list in `tpl_nav_root.html` must match the locales actually rendered (currently 8)

## Verification

No automated build exists in this workspace. After edits, check manually:

- Every `${key}` used in changed pages has a matching key in the applicable `../lang/website/**` file
- Every `${@import ...}` target exists under `tpl/`

## Child DOX Index

None — leaf scope.
