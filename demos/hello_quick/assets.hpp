#pragma once

#include "pascal_compat.hpp"
#include "bmfont.hpp"

TBMFont defaultFont;
TBMFontGlyph defaultFontGlyphs[96];  // 32..126

LongInt imgCursor;
LongInt imgDosuEXE[2];

// BMFont boilerplate
export PBMFont defaultFontPtr() {
  return &defaultFont;
}

export PBMFontGlyph defaultFontGlyphsPtr() {
  return defaultFontGlyphs;
}

void printDefault(const char* text, const SmallInt x, const SmallInt y) {
  printBMFont(defaultFont, defaultFontGlyphs, text, x, y);
}

Word measureDefault(const char* text) {
  return measureBMFont(defaultFontGlyphs, text);
}

// Asset boilerplate
export void setImgCursor(const LongInt imgHandle) {
  imgCursor = imgHandle;
}

export void setImgDosuEXE(const LongInt imgHandle, const SmallInt idx) {
  imgDosuEXE[idx] = imgHandle;
}
