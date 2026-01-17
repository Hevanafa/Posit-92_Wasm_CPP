#pragma once

#include <string>

#include "pascal_compat.hpp"

std::string i32str(const LongInt value) {
  return std::to_string(value);
}

std::string f32str(const double value) {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%.4f", value);
  return std::string(buffer);
}

std::string toFixed(const double value, const SmallInt decimals) {
  char buffer[32];

  if (decimals <= 0) {
    snprintf(buffer, sizeof(buffer), "%.0f", value);
    return std::string(buffer);
  }

  snprintf(buffer, sizeof(buffer), ("%." + i32str(decimals) + "f").c_str(), value);
  return std::string(buffer);
}
