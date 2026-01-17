#pragma once

#include <string>

#include "pascal_compat.hpp"

const char* i32str(const LongInt value) {
  static char result[16];
  snprintf(result, sizeof(result), "%d", value);
  return result;
}

std::string f32str(const double value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%.4f", value);
  return std::string(buffer);
}

std::string toFixed(const double value, SmallInt decimals) {
  char buffer[32];
  decimals = decimals < 0 ? 0 : decimals;

  snprintf(buffer, sizeof(buffer), "%.*f", decimals, value);
  return std::string(buffer);
}
