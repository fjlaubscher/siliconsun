---
title: Pan the view while a scroll key is held
category: feature
release: 0.2.0
targets:
- type: key
  id: ScrollWhileHeld
  effect: added
- type: command
  id: ScrollNorth
  effect: changed
- type: command
  id: ScrollSouth
  effect: changed
- type: command
  id: ScrollEast
  effect: changed
- type: command
  id: ScrollWest
  effect: changed
- type: key
  id: ScrollRate
  effect: changed
- type: key
  id: ScrollMultiplier
  effect: changed
credit:
- fjlaubscher
---

Holding a scroll key pans the tactical view, slowly at first and then faster, up to the speed `ScrollRate` under `[Options]` in `SUN.INI` allows, and `ScrollMultiplier` under `[AudioVisual]` in `rules.ini` scales each step. A press used to move the view 34 pixels and then stop. `ScrollWhileHeld=no` under `[siliconsun]` in `SUN.INI` keeps that single step, and a missing `ScrollWhileHeld` key pans while the scroll key is held.
