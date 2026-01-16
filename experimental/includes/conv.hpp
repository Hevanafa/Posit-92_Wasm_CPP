#pragma once

#include <string>
#include "pascal_compat.hpp"

std::string i32str(const LongInt value) {
  return std::to_string(value);
}
