#pragma once

#include "pascal_compat.hpp"

longint imgCGA8x8;

export void setImgCGA8x8(longint imgHandle) {
  imgCGA8x8 = imgHandle;
}
