#pragma once

#include <emscripten.h>
#include <stdint.h>

#include "pascal_compat.hpp"

export PByte WasmGetMem(const longword bytes) {
  return (PByte) malloc(bytes);
}