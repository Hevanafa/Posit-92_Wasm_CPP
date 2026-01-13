#include <emscripten.h>
#include <stdint.h>

#include "posit_92.hpp"
#include "includes\vga.h"

extern "C" {
  void signalDone();
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