#pragma once

#include <string>

#include "pascal_compat.hpp"

extern "C" {
  extern SmallInt getLoadingActual();
  extern SmallInt getLoadingTotal();
}
