#pragma once

#include <string>

extern "C" {
  extern void jsPanicHalt(const PByte textPtr, const size_t textLen);
}

void panicHalt(const std::string& msg) {
  byte msgBuffer[256];

  for (word a = 0; a < msg.length(); a++)
    msgBuffer[a] = msg[a];

  jsPanicHalt(msgBuffer, msg.length());
}
