#pragma once

#include "pascal_compat.hpp"

byte getAlpha(const longword colour) {
  return colour >> 24 & 0xFF
}

longword solidify(const longword colour) {
  return (colour & 0xFF000000 > 0)
    ? colour | 0xFF000000
    : colour;
}

void vline(
  smallint x0, smallint x1, smallint y,
  const longword colour)
{
  smallint x;
  longword solid;
}

void line(smallint x0, smallint y0, smallint x1, smallint y1, longword colour) {
  smallint dx, dy, sx, sy, err, e2;
  longword solid;

  if (getAlpha(colour) == 0) return;
  solid = solidify(colour);

  if (x0 == x1) {
    vline(x0, y0, y1, solid);
    return;
  }

  if (y0 == y1) {
    // hline(x0, x1, y0, solid);
    return;
  }

  // TODO: Implement line rendering
}