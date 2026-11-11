---
key: ScrollWhileHeld
scope: client-settings
label: Scroll while held
summary: Pans the tactical view while a scroll key is held.
see_also: [ScrollRate, ScrollMultiplier, AutoScroll]
when_omitted:
  kind: value
  value: "yes"
---

`ScrollWhileHeld=yes` pans the tactical view while a scroll key is held. The view speeds up the way it does at a screen edge: [`ScrollRate`](/keys/scrollrate/) sets the fastest step, and [`ScrollMultiplier`](/keys/scrollmultiplier/) scales every step. Releasing the key slows the view to a stop.

North and east held together pan north-east, and the other three corners do the same. North and south held together stop the pan, as do east and west.

While a message is being typed, the view slows to a stop as if the scroll key were released.

`no` moves the view 34 pixels once for each press of a scroll key. [`ScrollRate`](/keys/scrollrate/) and [`ScrollMultiplier`](/keys/scrollmultiplier/) do not change that step.

The key is read from `[siliconsun]` in `SUN.INI` at startup. No dialog offers it. Leaving the options menu writes the value currently in force.
