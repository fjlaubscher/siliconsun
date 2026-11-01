---
title: Setup screen for the freeware game data
category: feature
release: 0.2.0
targets:
- type: command
  id: launch:data-directory
  effect: changed
breaking: false
credit:
- fjlaubscher
---

A game with no `TIBSUN.MIX` shows a setup screen that downloads the freeware files, or copies them from a folder. Base game and music are included. Campaign movies and Firestorm are optional, and Firestorm's movies are included only when both are selected. The files are written into the data directory. An interactive launch creates a missing default data directory. A `-DATADIR` path that is not there is still refused. A directory that already holds `TIBSUN.MIX` is left unchanged. Headless and spawned runs do not show the screen.
