#pragma once

#include <emscripten.h>
#include <stdint.h>

#include "pascal_compat.hpp"

// Required for Pascal compatibility
export void initHeap(const longword startAddr, const longword heapSize) {
}

export PByte WasmGetMem(const longword bytes) {
  return (PByte) malloc(bytes);
}