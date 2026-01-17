#pragma once

#include "pascal_compat.hpp"

Word
  vgaWidth = 320,
  vgaHeight = 200;
LongWord bufferSize = vgaWidth * vgaHeight * 4;

PByte surface = nullptr;

extern "C" {
  extern void vgaFlush();
}

export PByte getSurfacePtr() { return surface; }

void initBuffer() {
  surface = (PByte) malloc(bufferSize);
}

void initCustomBuffer(const Word width, const Word height) {
  vgaWidth = width;
  vgaHeight = height;
  bufferSize = vgaWidth * vgaHeight * 4;

  surface = (PByte) malloc(bufferSize);
}

void cls(LongWord colour) {
  // ARGB to RGBA
  for (int i=0; i < vgaWidth * vgaHeight; i++) {
    surface[i * 4 + 3] = (colour >> 24) & 0xff;
    surface[i * 4] = (colour >> 16) & 0xff;
    surface[i * 4 + 1] = (colour >> 8) & 0xff;
    surface[i * 4 + 2] = colour & 0xff;
  }
}

void unsafePset(SmallInt x, SmallInt y, LongWord colour) {
  LongWord offset = (x + y * vgaWidth) * 4;
  // ARGB to RGBA
  surface[offset + 3] = (colour >> 24) & 0xFF;
  surface[offset] = (colour >> 16) & 0xFF;
  surface[offset + 1] = (colour >> 8) & 0xFF;
  surface[offset + 2] = colour & 0xFF;
}

void pset(SmallInt x, SmallInt y, LongWord colour) {
  if (x >= vgaWidth || x < 0 || y >= vgaHeight || y < 0) return;
  unsafePset(x, y, colour);
}
