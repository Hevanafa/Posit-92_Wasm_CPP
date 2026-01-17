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

Word printBMFontChar(
  const TBMFont font,
  const TBMFontGlyph fontGlyphs[],
  const char ch,
  const SmallInt x,
  const SmallInt y
) {
  Byte charcode;
  SmallInt glyphIdx;
  TBMFontGlyph glyph;

  charcode = ch;

  // Assuming the starting charcode is always 32
  glyphIdx = charcode - 32;

  // if (glyphIdx in [low(fontGlyphs)..high(fontGlyphs)]) {
  // if (std::begin(fontGlyphs) <= glyphIdx && glyphIdx <= std::end(fontGlyphs)) {

  // TODO: Implement something like glyphCount to check its range
  if (glyphIdx >= 0 && glyphIdx < 95) {
    glyph = fontGlyphs[glyphIdx];

    sprRegion(
      font.imgHandle,
      glyph.x, glyph.y,
      glyph.width, glyph.height,
      x + glyph.xoffset, y + glyph.yoffset);
    
    return glyph.xadvance;
  } else
    return 0;
}

Word printBMFont(
  const TBMFont font,
  const TBMFontGlyph fontGlyphs[],
  const std::string text,
  const SmallInt x,
  const SmallInt y
) {
  Word a;
  char ch;
  SmallInt left = 0;

  for (a = 0; a < text.length(); a++) {
    ch = text[a];
    left += printBMFontChar(font, fontGlyphs, ch, x + left, y);
  }

  return left;
}

// TODO: Measure BMFont
