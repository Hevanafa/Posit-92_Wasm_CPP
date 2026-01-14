#pragma once

#include "pascal_compat.hpp"
#include "conv.hpp"
#include "img_ref.hpp"
#include "vga.hpp"
#include "panic.hpp"

void spr(const longint imgHandle, const smallint x, const smallint y) {
  PImageRef image;
  smallint px, py;
  longword offset;
  byte a;
  longword colour;

  if (!isImageSet(imgHandle)) return;

  image = getImagePtr(imgHandle);
  // data = PByte(image^.dataPtr);
  // writeLog('offset: ' + i32str(offset));

  if (image->allocSize == 0)
    panicHalt("imgHandle " + i32str(imgHandle) + " allocSize is 0!");
  
  // writeLog('allocSize: ' + i32str(image^.allocSize));

  for (py = 0; py < image->height; py++)
  for (px = 0; px < image->width; px++) {
    if ((x + px >= vgaWidth) || (x + px < 0)
      || (y + py >= vgaHeight) || (y + py < 0)) continue;

    // offset to ImageData buffer
    offset = (px + py * image->width) * 4;

    a = image->dataPtr[offset + 3];
    if (a < 255) continue;

    colour = unsafeSprPget(image, px, py);
    unsafePset(x + px, y + py, colour);
  }
}