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
  Byte a;
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

void sprRegion(
  const longint imgHandle,
  const smallint srcX, const smallint srcY, const smallint srcW, const smallint srcH,
  const smallint destX, const smallint destY)
{
  PImageRef image;
  smallint a, b;
  smallint sx, sy;
  longint srcPos;
  Byte alpha;
  longword colour;

  if (!isImageSet(imgHandle)) return;

  image = getImagePtr(imgHandle);

  // for b:=0 to srcH - 1 do
  // for a:=0 to srcW - 1 do begin
  for (b = 0; b < srcH; b++)
  for (a = 0; a < srcW; a++) {
    if ((destX + a >= vgaWidth) || (destX + a < 0)
      || (destY + b >= vgaHeight) || (destY + b < 0)) continue;

    sx = srcX + a;
    sy = srcY + b;
    srcPos = (sx + sy * image->width) * 4;

    alpha = image->dataPtr[srcPos + 3];
    if (alpha < 255) continue;

    colour = unsafeSprPget(image, sx, sy);
    unsafePset(destX + a, destY + b, colour);
  }
}
