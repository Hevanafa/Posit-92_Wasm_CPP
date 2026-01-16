#include <emscripten.h>

#include "pascal_compat.hpp"

#include "logger.hpp"
#include "vga.hpp"
#include "wasm_heap.hpp"

bool once = false;

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

  if (!once) {
    once = true;
    writeLog("surface bytes");
    for (a=0; a<20; a++)
      writeLogI32(surface[a]);
  }

  vgaFlush();
}
