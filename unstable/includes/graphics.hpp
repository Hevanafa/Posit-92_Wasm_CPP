#pragma once

#include "pascal_compat.hpp"

void line(smallint x0, smallint y0, smallint x1, smallint y1, longword colour) {
  smallint dx, dy, sx, sy, err, e2;
  longword solid;

  if (colour & 0xFF000000 == 0) return;
  solid = colour | 0xFF000000;

  if (x0 == x1) {
    vline(x0, y0, y1, solid);
    return;
  }

  if (y0 == y1) {
    hline(x0, x1, y0, solid);
    return;
  }

  // TODO: Implement line rendering
}