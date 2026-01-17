#pragma once

#include <cstdio>

#include "pascal_compat.hpp"

const char* i32str(const LongInt value) {
  static char result[16];
  snprintf(result, sizeof(result), "%d", value);
  return result;
}

const char* f32str(const double value) {
  static char buffer[32];
  snprintf(buffer, sizeof(buffer), "%.4f", value);
  return buffer;
}

const char* toFixed(const double value, SmallInt decimals) {
  static char buffer[32];
  decimals = decimals < 0 ? 0 : decimals;

  snprintf(buffer, sizeof(buffer), "%.*f", decimals, value);
  return buffer;
}
