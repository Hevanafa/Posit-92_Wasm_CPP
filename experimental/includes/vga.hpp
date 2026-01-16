#pragma once

#include "pascal_compat.hpp"

const word
  vgaWidth = 320,
  vgaHeight = 200;
const longword bufferSize = vgaWidth * vgaHeight * 4;

PByte surface = nullptr;

extern "C" {
  extern void vgaFlush();
}

export PByte getSurfacePtr() { return surface; }

void initBuffer() {
  surface = (PByte) malloc(bufferSize);
}

void cls(longword colour) {
  Byte r, g, b, a;

  a = colour >> 24 & 0xff;
  r = colour >> 16 & 0xff;
  g = colour >> 8 & 0xff;
  b = colour & 0xff;

  for (int i=0; i < vgaWidth * vgaHeight; i++) {
    // RGBA
    surface[i * 4] = r;
    surface[i * 4 + 1] = g;
    surface[i * 4 + 2] = b;
    surface[i * 4 + 3] = a;
  }
}

void unsafePset(smallint x, smallint y, longword colour) {
  longword offset = (x + y * vgaWidth) * 4;
  // ARGB to RGBA
  surface[offset] = colour & 0x00FF0000 >> 16;
  surface[offset + 1] = colour & 0x0000FF00 >> 8;
  surface[offset + 2] = colour & 0x000000FF;
  surface[offset + 3] = colour & 0xFF000000 >> 24;
}

void pset(smallint x, smallint y, longword colour) {
  if (x >= vgaWidth || x < 0 || y >= vgaHeight || y < 0) return;
  unsafePset(x, y, colour);
}
