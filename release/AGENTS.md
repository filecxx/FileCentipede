# Release artifacts (release/)

## Purpose

Published, downloadable artifacts: versioned desktop builds for Windows and Linux, browser extension packages, and the PAD catalog file. These are served by the website's download pages and referenced by the software update feed.

## Ownership

- Owns: artifact inventory and naming
- Does not own: the update feed `../update.json`, download page markup (`../tpl/download.html`)

## Local Contracts

- Desktop builds: `filecxx_<version>_<win|linux>_x64.zip`, plus `filecxx_latest_<win|linux>_x64.zip` copies — the `latest` files must always be copies of the newest version
- Extension packages: `chrome.crx` / `chrome.zip` (MV2), `chrome_mv3.crx` / `chrome_mv3.zip` (MV3), `firefox.xpi`
- `FileCentipede_pad.xml`: PAD catalog file for download sites, must carry the current version
- `../update.json` is the software update feed: its `version`, magnet `uri_*` fields (which name archive files), and `checksum_*` fields must match the artifacts present here

## Work Guidance

- Binaries are opaque outputs: never edit in place; add new-version archives and refresh the `filecxx_latest_*` copies together
- Shipping a version = new archives here plus a matching `../update.json` entry in the same change

## Verification

No automated framework exists. Manual check when touching releases: `update.json` `version` matches the newest `filecxx_<version>_*` archives here, and the filenames referenced by its magnet URIs exist in this folder.

## Child DOX Index

None — leaf scope.
