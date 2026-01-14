#pragma once

#include "pascal_compat.hpp"
#include "vga.hpp"

byte getAlpha(const longword colour) {
  return colour >> 24 & 0xFF;
}

longword solidify(const longword colour) {
  return ((colour & 0xFF000000) > 0)
    ? colour | 0xFF000000
    : colour;
}

void vline(
  smallint x, smallint y0, smallint y1,
  const longword colour)
{
  smallint y, temp;

  if (getAlpha(colour) == 0) return;
  if ((x < 0) || (x >= vgaWidth)) return;

  longword solid = solidify(colour);

  if (y1 < y0) {
    temp = y0; y0 = y1; y1 = temp;
  }

  if (y0 < 0) y0 = 0;
  if (y1 >= vgaHeight) y1 = vgaHeight - 1;
  if (y0 > y1) return;

  for (y = y0; y <= y1; y++)
    unsafePset(x, y, solid);
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