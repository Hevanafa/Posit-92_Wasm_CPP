#pragma once

#include <string>
#include <sstream>  // ostringstream, fixed
#include <iomanip>  // setprecision

#include "pascal_compat.hpp"

std::string i32str(const LongInt value) {
  return std::to_string(value);
}

std::string f32str(const double value) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(4) << value;
  return oss.str();
}
