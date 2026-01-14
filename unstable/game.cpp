#include <emscripten.h>
#include <stdint.h>

#include "includes/pascal_compat.hpp"
#include "includes/vga.hpp"

extern "C" {
  extern void signalDone();
  extern void vgaFlush();
}

export void cleanup() {
  
}

export void init() {
  initBuffer();
}

export void update() {

}

export void draw() {
  cls(0xFF6495ED);

  vgaFlush();
}
