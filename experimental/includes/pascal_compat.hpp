#pragma once

#include <emscripten.h>
#include <stdint.h>

#define export extern "C" EMSCRIPTEN_KEEPALIVE

using PByte = uint8_t*;

using ShortInt = char;
using Byte = unsigned char;
using SmallInt = short;
using Word = unsigned short;
using LongInt = int;
using LongWord = unsigned int;

using int64 = long;
using uint64 = unsigned long;
