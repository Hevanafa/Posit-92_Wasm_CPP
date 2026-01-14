#pragma once
#include "../posit-92.hpp"

const word
  vgaWidth = 320,
  vgaHeight = 200;
const longword bufferSize = vgaWidth * vgaHeight * 4;

uint8_t* surface = nullptr;

export PByte getSurfacePtr() { return surface; }

void initBuffer() {
  surface = (PByte) malloc(bufferSize);
}

void cls(longword colour) {
  byte r, g, b, a;

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
