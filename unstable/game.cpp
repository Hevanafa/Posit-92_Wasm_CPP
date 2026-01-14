#include <emscripten.h>
#include <stdint.h>
#include <math.h>

#include "includes/pascal_compat.hpp"
#include "includes/vga.hpp"
#include "includes/graphics.hpp"

extern "C" {
  extern void signalDone();
  extern void vgaFlush();
}

const longword white = 0xFFFFFFFF;

// Game state
double angle = 0.0;

export void cleanup() {
  
}

export void init() {
  initBuffer();
}

export void afterInit() {

}

export void update() {

}

export void draw() {
  double x, y;

  cls(0xFF6495ED);

  angle += 0.1667;
  x = 50 + sin(angle) * 10;
  y = 50 + cos(angle) * 10;
  line(50, 50, (smallint) x, (smallint) y, white);

  vgaFlush();
}
