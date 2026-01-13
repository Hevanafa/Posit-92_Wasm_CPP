#include "..\posit_92.hpp"

const word
  vgaWidth = 320,
  vgaHeight = 200;

uint8_t* surface = nullptr;

void initBuffer() {
  surface = (PByte) malloc(bufferSize);
}

void cls(longword colour) {
  byte r, g, b, a;
  
  a = colour shr 24 & 0xff;
  r = colour shr 16 & 0xff;
  g = colour shr 8 & 0xff;
  b = colour & 0xff;

  for (int i=0; i < vgaWidth * vgaHeight; i++) {
    // RGBA
    surface[i * 4] = 0x64;
    surface[i * 4 + 1] = 0x95;
    surface[i * 4 + 2] = 0xED;
    surface[i * 4 + 3] = 0xFF;
  }
}
