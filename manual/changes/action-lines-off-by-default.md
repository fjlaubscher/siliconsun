---
title: Turn action lines off by default
category: feature
release: 0.2.0
targets:
- type: key
  id: UnitActionLines
  effect: changed
credit:
- fjlaubscher
---

`UnitActionLines` under `[Options]` in `SUN.INI` defaults to `no`. Selected objects no longer draw action lines — the line to their target, the line along their route, and the lines through queued destinations — unless the setting is turned on. Set `UnitActionLines=yes` to draw them.
