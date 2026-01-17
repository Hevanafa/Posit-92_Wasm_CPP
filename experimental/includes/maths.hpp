#pragma once

#include "pascal_compat.hpp"

// LongInt trunc(const double value) {
//   return (LongInt)value;
// }

double frac(const double value) {
  return std::modf(value, nullptr);
}

double clamp(const double value, const double min, const double max) {
  return value < min ? min
    : value > max ? max
    : value;
}
