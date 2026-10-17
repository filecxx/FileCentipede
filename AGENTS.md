# DOX framework

- DOX is highly performant AGENTS.md hierarchy installed here
- Agent must follow DOX instructions across any edits

## Project Overview

File Centipede (filecxx.com) public repository: the static website, translation sources, release artifacts, and partial desktop-app source.

- Git: `origin` = `https://github.com/vendoriaai/FileCentipede` (user's fork); upstream = `https://github.com/filecxx/FileCentipede`. Fork `main` carries the fork's additions (DOX docs, `themes/`); upstream contributions are filed from dedicated clean branches built on upstream `main` (e.g. `upstream-pr` — no DOX files, rebased onto upstream when it moves). `commit.sh`, `update.sh`, and `certbot.sh` target the original author's GitHub repo and web server — do not run them against the fork

- Website: `tpl/` is the master template (`${key}` placeholders + `${@import ...}` includes); the locale folders `de_DE/ en_US/ id_ID/ ko_KR/ ru_RU/ tr_TR/ zh_CN/ zh_TW/` are generated renders — edit `tpl/` plus `lang/website/`, never hand-edit locale folders
- Translations: `lang/` holds the only string sources — `website/*.lang`, `software/*.lang` (key=value; keys ending in `_` may contain HTML), `browser_extension/<locale>/messages.json`
- Releases: `release/` artifacts are coupled to the root `update.json` update feed — see `release/AGENTS.md`
- Shared web assets: `style/`, `script/`, `images/`; root shell pages redirect visitors (`index.html` and `activation_code.html` by browser language to a locale site, `troubleshooting.html` to GitHub issues); the locale lists in those pages and in `tpl/tpl_nav_root.html` must stay in sync with the rendered locales
- `.gitattributes` intentionally marks `*.js`, `*.css`, `*.html` as C++ for linguist stats — leave it alone
- `CNAME` pins GitHub Pages to www.filecxx.com; `.github/` holds issue templates and a disabled README-translation workflow (`workflows/readme.yml.bak`)
- `README.md` plus its 15 language variants are the product readme; keep the language link bar at its top in sync with the README files actually present
- `FileCentipede-main/` and `FileCentipede.wiki/` are empty placeholder directories

## Core Contract

- AGENTS.md files are binding work contracts for their subtrees
- Work products, source materials, instructions, records, assets, and durable docs must stay understandable from the nearest applicable AGENTS.md plus every parent AGENTS.md above it

## Read Before Editing

1. Read the root AGENTS.md
2. Identify every file or folder you expect to touch
3. Walk from the repository root to each target path
4. Read every AGENTS.md found along each route
5. If a parent AGENTS.md lists a child AGENTS.md whose scope contains the path, read that child and continue from there
6. Use the nearest AGENTS.md as the local contract and parent docs for repo-wide rules
7. If docs conflict, the closer doc controls local work details, but no child doc may weaken DOX

Do not rely on memory. Re-read the applicable DOX chain in the current session before editing.

## Update After Editing

Every meaningful change requires a DOX pass before the task is done.

Update the closest owning AGENTS.md when a change affects:

- purpose, scope, ownership, or responsibilities
- durable structure, contracts, workflows, or operating rules
- required inputs, outputs, permissions, constraints, side effects, or artifacts
- user preferences about behavior, communication, process, organization, or quality
- AGENTS.md creation, deletion, move, rename, or index contents

Update parent docs when parent-level structure, ownership, workflow, or child index changes. Update child docs when parent changes alter local rules. Remove stale or contradictory text immediately. Small edits that do not change behavior or contracts may leave docs unchanged, but the DOX pass still must happen.

## Hierarchy

- Root AGENTS.md is the DOX rail: project-wide instructions, global preferences, durable workflow rules, and the top-level Child DOX Index
- Child AGENTS.md files own domain-specific instructions and their own Child DOX Index
- Each parent explains what its direct children cover and what stays owned by the parent
- The closer a doc is to the work, the more specific and practical it must be

## Child Doc Shape

- Create a child AGENTS.md when a folder becomes a durable boundary with its own purpose, rules, responsibilities, workflow, materials, or quality standards
- Work Guidance must reflect the current standards of the project or user instructions; if there are no specific standards or instructions yet, leave it empty
- Verification must reflect an existing check; if no verification framework exists yet, leave it empty and update it when one exists

Default section order:
- Purpose
- Ownership
- Local Contracts
- Work Guidance
- Verification
- Child DOX Index

## Style

- Keep docs concise, current, and operational
- Document stable contracts, not diary entries
- Put broad rules in parent docs and concrete details in child docs
- Prefer direct bullets with explicit names
- Do not duplicate rules across many files unless each scope needs a local version
- Delete stale notes instead of explaining history
- Trim obvious statements, repeated rules, misplaced detail, and warnings for risks that no longer exist

## Closeout

1. Re-check changed paths against the DOX chain
2. Update nearest owning docs and any affected parents or children
3. Refresh every affected Child DOX Index
4. Remove stale or contradictory text
5. Run existing verification when relevant
6. Report any docs intentionally left unchanged and why

## User Preferences

When the user requests a durable behavior change, record it here or in the relevant child AGENTS.md

## Child DOX Index

Child AGENTS.md files — read the applicable one before editing inside its scope:

- `tpl/AGENTS.md` — master website template: page structure, placeholders, includes, and the locale render contract
- `lang/AGENTS.md` — translation sources for the website, desktop software, and browser extension
- `source_code/AGENTS.md` — partial C++/Qt desktop app source (`fileu/`, `fileu_launch/`)
- `release/AGENTS.md` — published binaries and extension packages, coupled to `update.json`
- `themes/AGENTS.md` — drop-in dark/light desktop-app theme pack with toolbar toggle (runtime `ui/css` + `icons/` overlay for an extracted app folder)

Folders without their own AGENTS.md — governed by this root doc:

- `de_DE/`, `en_US/`, `id_ID/`, `ko_KR/`, `ru_RU/`, `tr_TR/`, `zh_CN/`, `zh_TW/` — generated locale websites; edit via `tpl/` + `lang/website/` (contract detailed in `tpl/AGENTS.md`)
- `images/`, `style/`, `script/` — shared website assets referenced by every locale site
- `public_lists/` — redirect stubs to github.com/filecxx/PublicLists discussions
- `.github/` — issue templates and the disabled README-translation workflow
- Root files: shell pages, `update.json`, `CNAME`, git/server helper scripts, README translations, `dht128.txt` (DHT bootstrap nodes)
- `FileCentipede-main/`, `FileCentipede.wiki/` — empty placeholder directories
