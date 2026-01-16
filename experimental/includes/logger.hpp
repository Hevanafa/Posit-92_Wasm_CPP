#pragma once

#include <emscripten.h>
#include <string>
#include "pascal_compat.hpp"

Byte logBuffer[256];

extern "C" {
  extern void flushLog();
}

export PByte getLogBuffer() {
  return logBuffer;
}

void writeLog(const std::string& msg) {
  Byte a;
  Word len;
  
  len = msg.length();

  // Cap length to 255
  if (len > 255) len = 255;

  logBuffer[0] = len;
  // for a:=1 to len do
  for (a = 1; a <= len; a++)
    logBuffer[a] = msg[a];

  // JS will read logBuffer
  flushLog();
}