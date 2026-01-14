#include <emscripten.h>
#include <stdint.h>

#include "includes/pascal_compat.hpp"
#include "includes/vga.hpp"
#include "includes/graphics.hpp"

extern "C" {
  extern void signalDone();
  extern void vgaFlush();
}

const longword white = 0xFFFFFFFF;

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
  cls(0xFF6495ED);
  // pset(10, 10, White);
  vline(10, 10, 30, white);
  hline(10, 30, 10, white);

  line(10, 10, 30, 30, white);

  vgaFlush();
}
