#include <emscripten.h>
#include <stdint.h>
#include <math.h>

#include "pascal_compat.hpp"
#include "vga.hpp"
#include "keyboard.hpp"
#include "graphics.hpp"
#include "timing.hpp"
#include "img_ref.hpp"
#include "img_ref_fast.hpp"
#include "logger.hpp"
#include "wasm_heap.hpp"

#include "assets.hpp"

extern "C" {
  extern void signalDone();
}

const Byte
  SC_ESC = 0x01;

const LongWord white = 0xFFFFFFFF;

// Game state variables
double angle = 0.0;
double gameTime = 0.0;

void printChar(const char c, const SmallInt x, const SmallInt y) {
  SmallInt row, col;
  row = c / 16;
  col = c % 16;
  sprRegion(imgCGA8x8, col * 8, row * 8, 8, 8, x, y);
}

void printSimple(const std::string& text, const SmallInt x, const SmallInt y) {
  SmallInt left = x;

  for (Word a = 0; a < text.length(); a++) {
    printChar(text[a], left, y);
    left += 8;
  }
}


export void cleanup() {
  
}

export void init() {
  initBuffer();
  initDeltaTime();
}

export void afterInit() {
  gameTime = 0.0;
}

export void update() {
  updateDeltaTime();

  if (isKeyDown(SC_ESC)) signalDone();

  // Update your game state here
  gameTime += dt;
}

export void draw() {
  double x, y;
  Word a;
  PImageRef image;

  cls(0xFF6495ED);

  spr(imgCGA8x8, 10, 10);
  // sprRegion(imgCGA8x8, 16, 16, 8, 8, 10, 10);
  // printSimple("Hello world!", 10, 10);

  angle += 0.1667;
  x = vgaWidth / 2 + sin(angle) * 10;
  y = vgaHeight / 2 + cos(angle) * 10;
  
  line(
    vgaWidth / 2, vgaHeight / 2,
    (SmallInt) x, (SmallInt) y, white);

  vgaFlush();
}
