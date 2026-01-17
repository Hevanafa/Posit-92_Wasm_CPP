#pragma once

#include "pascal_compat.hpp"
#include "conv.hpp"
#include "logger.hpp"
#include "panic.hpp"

struct TImageRef {
  SmallInt width;
  SmallInt height;
  LongWord allocSize;
  PByte dataPtr;
};
using PImageRef = TImageRef*;

const SmallInt
  MaxImageRefs = 256;

TImageRef imageRefs[MaxImageRefs + 1];  // index 0 is unused

bool isImageSet(const LongInt imgHandle) {
  if (imgHandle < 0 || imgHandle > MaxImageRefs)
    return false;

  return imageRefs[imgHandle].allocSize > 0;
}

PImageRef getImagePtr(const LongInt imgHandle) {
  if (imgHandle < 1 || imgHandle > MaxImageRefs)
    return nullptr;

  return &imageRefs[imgHandle];
}

SmallInt findEmptyImageRefSlot() {
  LongInt a;

  for (a = 1; a <= MaxImageRefs; a++)
    if (!isImageSet(a))
      return a;

  return -1;
}

export void registerImageRef(const LongInt imgHandle, const PByte dataPtr, const SmallInt w, const SmallInt h) {
  SmallInt idx = findEmptyImageRefSlot();

  if (idx < 0) panicHalt("Image ref pool is full!");

  imageRefs[imgHandle].width = w;
  imageRefs[imgHandle].height = h;
  imageRefs[imgHandle].allocSize = w * h * 4;
  imageRefs[imgHandle].dataPtr = dataPtr;

  writeLog(i32str(w) + ", " + i32str(h));
  writeLog("allocSize: ");
  writeLogI64(imageRefs[imgHandle].allocSize);

  writeLog("offset");
  LongWord offset = reinterpret_cast<LongWord>(dataPtr);
  writeLogI64(offset);

  writeLog("imgHandle comparison for handle " + i32str(imgHandle));
  writeLogI64(reinterpret_cast<LongWord>(imageRefs[imgHandle].dataPtr));
  writeLogI64(reinterpret_cast<LongWord>(getImagePtr(imgHandle)->dataPtr));

  writeLog("20 bytes (from direct access)");
  for (Word a = 60; a < 80; a++)
    writeLogI32(imageRefs[imgHandle].dataPtr[a]);

  writeLog("20 bytes (from pointer)");
  for (Word a = 60; a < 80; a++)
    writeLogI32(getImagePtr(imgHandle)->dataPtr[a]);
}

LongWord unsafeSprPget(const PImageRef image, const SmallInt x, const SmallInt y) {
  LongWord offset = (x + y * image->width) * 4;
  
  return (image->dataPtr[offset + 3] << 24)
    | (image->dataPtr[offset] << 16)
    | (image->dataPtr[offset + 1] << 8)
    | image->dataPtr[offset + 2];
}
