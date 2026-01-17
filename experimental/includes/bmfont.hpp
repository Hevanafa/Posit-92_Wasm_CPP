#pragma once

#include <string>

#include "pascal_compat.hpp"

struct TBMFontGlyph {
  Word id;
  Word x, y, width, height;
  SmallInt xoffset, yoffset;
  SmallInt xadvance;
};

struct __attribute__((packed))
TBMFont {
  char face[16];
  char filename[64];
  Word lineHeight;
  LongInt imgHandle;
};

using PBMFontGlyph = TBMFontGlyph*;
using PBMFont = TBMFont*;

void printBMFont(
  const TBMFont font,
  const TBMFontGlyph fontGlyphs[],
  const std::string text,
  const SmallInt x,
  const SmallInt y)
{
  Word a;
  char ch;
  SmallInt left = 0;

  for (a = 0; a < text.length(); a++) {
    ch = text[a];
    left += printBMFontChar(font, fontGlyphs, ch, x + left, y);
  }
}
