#pragma once

#include "pascal_compat.hpp"

extern "C" {
  extern void toggleFullscreen();
  extern bool getFullscreenState();
  extern void fitCanvas();
  extern void endFullscreen();
}
