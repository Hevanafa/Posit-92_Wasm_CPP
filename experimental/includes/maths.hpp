#pragma once

double clamp(const double value, const double min, const double max) {
  return value < min ? min
    : value > max ? max
    : value;
}