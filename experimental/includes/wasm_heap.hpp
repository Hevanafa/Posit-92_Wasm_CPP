#pragma once

#include <emscripten.h>
#include <stdint.h>

#include "pascal_compat.hpp"

// Required for Pascal compatibility
export void initHeap(const LongWord startAddr, const LongWord heapSize) {
}

export PByte WasmGetMem(const LongWord bytes) {
  return (PByte) malloc(bytes);
}