#pragma once

#include <emscripten.h>
#include <string>
// #include "pascal_compat.hpp"

uint8_t logBuffer[256];

extern "C" {
  extern void flushLog();
}

extern "C" EMSCRIPTEN_KEEPALIVE uint8_t* getLogBuffer() {
  return logBuffer;
}

void writeLog(const std::string& msg) {
  char a;
  unsigned short len;
  
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