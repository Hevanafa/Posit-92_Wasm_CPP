#include <emscripten.h>
#include <stdint.h>
#include <math.h>

#include "includes/pascal_compat.hpp"
#include "includes/vga.hpp"
#include "includes/keyboard.hpp"
#include "includes/graphics.hpp"
#include "includes/timing.hpp"

#include "assets.hpp"

extern "C" {
  extern void signalDone();
  extern void vgaFlush();
}

const byte
  SC_ESC = 0x01;

const longword white = 0xFFFFFFFF;

// Game state variables
double angle = 0.0;
double gameTime = 0.0;

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

  cls(0xFF6495ED);

  angle += 0.1667;
  x = vgaWidth / 2 + sin(angle) * 10;
  y = vgaHeight / 2 + cos(angle) * 10;
  
  line(
    vgaWidth / 2, vgaHeight / 2,
    (smallint) x, (smallint) y, white);

  vgaFlush();
}
