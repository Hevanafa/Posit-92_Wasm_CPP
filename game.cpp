#include <emscripten.h>
#include <stdint.h>

#include "posit_92.hpp"
#include "includes/vga.h"


export void init() {
  initBuffer();
}