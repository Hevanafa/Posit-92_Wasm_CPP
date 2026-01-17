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

/**
 * Doesn't work because of how unpredictable `malloc` is
 * 
 * @deprecated
 */
export void registerImageRefLegacy(const LongInt imgHandle, const PByte tempPtr, const SmallInt w, const SmallInt h) {
  SmallInt idx = findEmptyImageRefSlot();

  if (idx < 0) panicHalt("Image ref pool is full!");

  LongWord allocSize = w * h * 4;

  imageRefs[imgHandle].width = w;
  imageRefs[imgHandle].height = h;
  imageRefs[imgHandle].allocSize = allocSize;
  imageRefs[imgHandle].dataPtr = (PByte) malloc(allocSize);

  memcpy(imageRefs[imgHandle].dataPtr, tempPtr, allocSize);
  free(tempPtr);
}

/**
 * Static image data pool: All image pixel data is stored here
 * 
 * We use a fixed pool instead of `malloc` because:
 * 
 * - `malloc()` in WASM can reuse freed addresses unpredictably
 * - WASM memory can relocate when it grows *and* invalidating pointers
 * 
 * This approach ensures stable addresses throughout the runtime
 **/
Byte imageDataPool[256 * 1024];
LongWord poolOffset = 0;

export void registerImageRef(const LongInt imgHandle, const PByte tempPtr, const SmallInt w, const SmallInt h) {
  LongWord allocSize = w * h * 4;

  if (poolOffset + allocSize > sizeof(imageDataPool))
    panicHalt("Image pool exhausted!");

  imageRefs[imgHandle].dataPtr = imageDataPool + poolOffset;
  memcpy(imageRefs[imgHandle].dataPtr, tempPtr, allocSize);

  imageRefs[imgHandle].width = w;
  imageRefs[imgHandle].height = h;
  imageRefs[imgHandle].allocSize = allocSize;

  poolOffset += allocSize;
  free(tempPtr);
}

LongWord unsafeSprPget(const PImageRef image, const SmallInt x, const SmallInt y) {
  LongWord offset = (x + y * image->width) * 4;
  
  return (image->dataPtr[offset + 3] << 24)
    | (image->dataPtr[offset] << 16)
    | (image->dataPtr[offset + 1] << 8)
    | image->dataPtr[offset + 2];
}
