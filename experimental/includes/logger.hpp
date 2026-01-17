#pragma once

#include <cstring>
#include "pascal_compat.hpp"

Byte logBuffer[256];

extern "C" {
  extern void flushLog();
  extern void writeLogI32(const LongInt value);
  extern void writeLogI64(const int64 value);
}

export PByte getLogBuffer() {
  return logBuffer;
}

void writeLog(const char* msg) {
  Byte a;
  Word len;
  
  len = strlen(msg);

  // Cap length to 255
  if (len > 255) len = 255;

  logBuffer[0] = len;
  strncpy((char*)&logBuffer[1], msg, len);

  // JS will read logBuffer
  flushLog();
}