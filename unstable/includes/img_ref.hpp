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

TImageRef imageRefs[MaxImageRefs];  // index 0 is unused

bool isImageSet(const longint imgHandle) {
  if (imgHandle <= 0) return;

  return imageRefs[imgHandle].allocSize > 0;
}

PImageRef getImagePtr(const longint imgHandle) {
  return &imageRefs[imgHandle];
}

smallint findEmptyImageRefSlot() {
  longint a;

  for (a = 1; a <= MaxImageRefs; a++)
    if (!isImageSet(a))
      return a;

  return -1;
}

void registerImageRef(const longint imgHandle, const PByte dataPtr, const smallint w, const smallint h) {
  smallint idx = findEmptyImageRefSlot();

  if (idx < 0) panicHalt('Image ref pool is full!');

  imageRefs[imgHandle].width = w;
  imageRefs[imgHandle].height = h;
  imageRefs[imgHandle].allocSize = w * h * 4;
  imageRefs[imgHandle].dataPtr = dataPtr;
}
