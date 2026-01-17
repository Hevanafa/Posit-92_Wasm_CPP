#pragma once

#include "pascal_compat.hpp"

#include "timing.hpp"

SmallInt actualFPS, lastFPS;
double lastFPSTime;  // in seconds

void initFPSCounter() {
  actualFPS = 0;
  lastFPS = 0;
  lastFPSTime = getTimer();
}

void incrementFPS() {
  actualFPS = actualFPS + 1;
  if (getTimer() - lastFPSTime >= 1.0) {
    lastFPSTime = getTimer();
    lastFPS = actualFPS;
    actualFPS = 1;
  }
}

SmallInt getLastFPS() {
  return lastFPS;
}
