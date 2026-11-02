---
title: Wait for the display's refresh by default
category: performance
release: 0.2.0
targets:
- type: key
  id: VSync
  effect: changed
credit:
- fjlaubscher
---

`VSync` under `[Video]` in `SUN.INI` defaults to `yes`. A fresh install now waits for the display's refresh before showing each frame, where it previously presented as soon as a frame was ready. Set `VSync=no` to present without waiting.
