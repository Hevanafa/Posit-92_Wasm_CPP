#include <emscripten.h>

#include "pascal_compat.hpp"

#include "logger.hpp"
#include "vga.hpp"
#include "wasm_heap.hpp"

export void init() {
  initBuffer();
}

export void afterInit() {
  writeLog("Hello from hello_minimal!");
}

export void update() {
}

export void draw() {
  Word a;

  cls(0xFF6495ED);

  vgaFlush();
}
