#pragma once

#include "pascal_compat.hpp"

const SmallInt
  MouseButtonNone = 0,
  MouseButtonLeft = 1,
  MouseButtonRight = 2,
  MouseButtonBoth = 3;

SmallInt mouseX, mouseY, mouseButton;

extern "C" {
  extern void hideCursor();
  extern void showCursor();

  extern SmallInt getMouseX();
  extern SmallInt getMouseY();
  extern SmallInt getMouseButton();
}

void updateMouse() {
  mouseX = getMouseX();
  mouseY = getMouseY();
  mouseButton= getMouseButton();
}
