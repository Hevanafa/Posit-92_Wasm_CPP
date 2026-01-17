#pragma once

#include "pascal_compat.hpp"

LongInt imgCGA8x8;

export void setImgCGA8x8(LongInt imgHandle) {
  imgCGA8x8 = imgHandle;
}
