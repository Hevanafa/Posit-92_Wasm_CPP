#include <emscripten.h>
#include <stdint.h>

#include "posit-92.hpp"
#include "includes\vga.h"

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
