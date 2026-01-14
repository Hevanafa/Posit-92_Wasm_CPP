#pragma once

#include <stdint.h>
#include "pascal_compat.hpp"

typedef struct {
  smallint width;
  smallint height;
  longword allocSize;
  const PByte dataPtr;
} TImageRef;

#define PImageRef TImageRef*

const smallint
  MaxImageRefs = 256;

TImageRef imageRefs[MaxImageRefs + 1];  // index 0 is unused

bool isImageSet(const longint imgHandle) {
  if (imgHandle < 0 || imgHandle > MaxImageRefs)
    return false;

  return imageRefs[imgHandle].allocSize > 0;
}

PImageRef getImagePtr(const longint imgHandle) {
  if (imgHandle < 1 || imgHandle > MaxImageRefs)
    return nullptr;

  return &imageRefs[imgHandle];
}

smallint findEmptyImageRefSlot() {
  longint a;

  for (a = 1; a <= MaxImageRefs; a++)
    if (!isImageSet(a))
      return a;

  return -1;
}

export void registerImageRef(const longint imgHandle, const PByte dataPtr, const smallint w, const smallint h) {
  smallint idx = findEmptyImageRefSlot();

  if (idx < 0) return;
  // TODO: if (idx < 0) panicHalt('Image ref pool is full!');

  imageRefs[imgHandle].width = w;
  imageRefs[imgHandle].height = h;
  imageRefs[imgHandle].allocSize = w * h * 4;
  imageRefs[imgHandle].dataPtr = dataPtr;
}

longword unsafeSprPget(const PImageRef image, const smallint x, const smallint y) {
  longword offset = (x + y * image->width) * 4;
  
  return (image->dataPtr[offset + 3] << 24)
    | (image->dataPtr[offset] << 16)
    | (image->dataPtr[offset + 1] << 8)
    | image->dataPtr[offset + 2];
}
