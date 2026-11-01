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

A game with no `TIBSUN.MIX` shows a setup screen that downloads the freeware files, or copies them from a folder. Tiberian Sun game data and music are included. Tiberian Sun campaign cinematics and Firestorm game data and music are optional. Firestorm campaign cinematics are optional on their own. The files are written into the data directory. An interactive launch creates a missing default data directory. A `-DATADIR` path that is not there is still refused. A directory that already holds `TIBSUN.MIX` is left unchanged. Headless and spawned runs do not show the screen.
