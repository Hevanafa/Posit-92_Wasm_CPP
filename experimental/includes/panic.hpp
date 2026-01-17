#pragma once

#include <cstring>
#include "pascal_compat.hpp"

extern "C" {
  extern void jsPanicHalt(const char* textPtr, const size_t textLen);
}

void panicHalt(const char* msg) {
  jsPanicHalt(msg, strlen(msg));
}
