#pragma once

#include <string>
#include "pascal_compat.hpp"

Byte logBuffer[256];

extern "C" {
  extern void flushLog();
  extern void writeLogI32(const LongInt value);
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
    logBuffer[a] = msg[a - 1];

  // JS will read logBuffer
  flushLog();
}