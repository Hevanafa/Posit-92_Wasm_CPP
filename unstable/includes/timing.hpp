#pragma once

double dt, lastFrameTime, currentTime;

extern "C" {
  extern double getTimer();
  extern double getFullTimer();
}

void initDeltaTime() {
  dt = 0.0;
  lastFrameTime = getTimer();
  currentTime = lastFrameTime;
}

void updateDeltaTime() {
  currentTime = getTimer();
  dt = currentTime - lastFrameTime;
  lastFrameTime = currentTime;
}
