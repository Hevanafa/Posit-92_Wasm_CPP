#pragma once

#include "pascal_compat.hpp"
#include "vga.hpp"

Byte getAlpha(const LongWord colour) {
  return colour >> 24 & 0xFF;
}

LongWord solidify(const LongWord colour) {
  return ((colour & 0xFF000000) > 0)
    ? colour | 0xFF000000
    : colour;
}

void hline(
  SmallInt x0, SmallInt x1, SmallInt y,
  const LongWord colour)
{
  SmallInt x;

  if (getAlpha(colour) == 0) return;
  LongWord solid = solidify(colour);

  if ((y < 0) || (y >= vgaHeight)) return;
  if (x1 < x0) {
    x = x0; x0 = x1; x1 = x;
  }

  if (x0 < 0) x0 = 0;
  if (x1 >= vgaWidth) x1 = vgaWidth - 1;
  if (x0 > x1) return;

  for (x = x0; x <= x1; x++)
    unsafePset(x, y, solid);
}

void vline(
  SmallInt x, SmallInt y0, SmallInt y1,
  const LongWord colour)
{
  SmallInt y, temp;

  if (getAlpha(colour) == 0) return;
  if ((x < 0) || (x >= vgaWidth)) return;

  LongWord solid = solidify(colour);

  if (y1 < y0) {
    temp = y0; y0 = y1; y1 = temp;
  }

  if (y0 < 0) y0 = 0;
  if (y1 >= vgaHeight) y1 = vgaHeight - 1;
  if (y0 > y1) return;

  for (y = y0; y <= y1; y++)
    unsafePset(x, y, solid);
}

void line(SmallInt x0, SmallInt y0, SmallInt x1, SmallInt y1, LongWord colour) {
  SmallInt dx, dy, sx, sy, err, e2;
  LongWord solid;

  if (getAlpha(colour) == 0) return;
  solid = solidify(colour);

  if (x0 == x1) {
    vline(x0, y0, y1, solid);
    return;
  }

  if (y0 == y1) {
    hline(x0, x1, y0, solid);
    return;
  }

  dx = abs(x1 - x0);
  dy = abs(y1 - y0);

  if (x0 < x1) sx = 1; else sx = -1;
  if (y0 < y1) sy = 1; else sy = -1;

  err = dx - dy;

  while ((x0 != x1) || (y0 != y1)) {
    pset(x0, y0, solid);
    e2 = 2 * err;

    if (e2 > -dy) {
      err = err - dy;
      x0 = x0 + sx;
    }

    if (e2 < dx) {
      err = err + dx;
      y0 = y0 + sy;
    }
  }

  pset(x0, y0, solid);
}
