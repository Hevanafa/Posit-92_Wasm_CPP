#include <emscripten.h>
#include <stdint.h>

#include "pascal_compat.hpp"

#include "logger.hpp"
#include "vga.hpp"
#include "wasm_heap.hpp"
// #include "logger.hpp"

export void init() {
  initBuffer();
}

export void afterInit() {
  writeLog("Hello from hello_minimal!");
}

export void update() {
}

export void draw() {
  cls(0x6495ED);

  vgaFlush();
}
