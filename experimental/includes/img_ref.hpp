#pragma once

#include <stdint.h>
#include "pascal_compat.hpp"
#include "panic.hpp"

typedef struct {
  SmallInt width;
  SmallInt height;
  LongWord allocSize;
  const PByte dataPtr;
} TImageRef;

#define PImageRef TImageRef*

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
}

LongWord unsafeSprPget(const PImageRef image, const SmallInt x, const SmallInt y) {
  LongWord offset = (x + y * image->width) * 4;
  
  return (image->dataPtr[offset + 3] << 24)
    | (image->dataPtr[offset] << 16)
    | (image->dataPtr[offset + 1] << 8)
    | image->dataPtr[offset + 2];
}
