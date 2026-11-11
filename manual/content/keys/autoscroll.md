---
key: AutoScroll
summary: Scrolls the tactical map while the pointer rests against the edge of the screen.
see_also: [ScrollRate, ScrollMethod, ScrollMultiplier, ScrollWhileHeld]
when_omitted:
  kind: value
  value: "yes"
---

`AutoScroll=no` turns edge scrolling off. Resting the pointer against the edge of the screen no longer moves the view, and the pointer keeps its normal shape instead of turning into a scroll arrow. The keyboard scroll keys, dragging with the right mouse button as [`ScrollMethod`](/keys/scrollmethod/) describes, and clicking the radar still move the view.

[`ScrollMultiplier`](/keys/scrollmultiplier/) scales edge scrolling, so it no longer scales the pointer at the edge while this is off. Keyboard scrolling while [`ScrollWhileHeld`](/keys/scrollwhileheld/) is on still uses it. [`ScrollRate`](/keys/scrollrate/) sets the speed of right-button dragging and of that keyboard scrolling, and keeps both effects.

The game controls dialog has the same switch. Closing the dialog with OK, or leaving it through its Sound or Keyboard button, applies the change and writes it to `sun.ini`. Cancel discards it.
