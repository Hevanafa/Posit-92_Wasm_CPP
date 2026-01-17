#pragma once

#include "pascal_compat.hpp"
#include "bmfont.hpp"

TBMFont defaultFont;
TBMFontGlyph defaultFontGlyphs[96];  // 32..126

export PBMFont defaultFontPtr() {
  return &defaultFont;
}

export PBMFontGlyph defaultFontGlyphsPtr() {
  return defaultFontGlyphs;
}

void printDefault(const std::string& text, const SmallInt x, const SmallInt y) {
  printBMFont(defaultFont, defaultFontGlyphs, text, x, y);
}
