#include "pascal_compat.hpp"

#include "conv.hpp"
#include "logger.hpp"
#include "vga.hpp"
#include "wasm_heap.hpp"
#include "maths.hpp"
#include "graphics.hpp"

// Game state
int t = 0;

// h, s, v: [0.0, 1.0]
LongWord HSVtoRGB(double h, double s, double v) {
  Byte r, g, b;
  SmallInt i;
  double f, p, q, t;

  h = clamp(h, 0.0, 1.0);
  s = clamp(s, 0.0, 1.0);
  v = clamp(v, 0.0, 1.0);

  // Greyscale
  if (s == 0.0) {
    r = (int)(v * 255);
    g = r;
    b = r;
    return 0xFF000000 | (r << 16) | (g << 8) | b;
  }

  // Convert hue to [0.0, 6.0]
  h = h * 6.0;
  i = (Byte)(h);
  f = h - i;

  p = v * (1.0 - s);
  q = v * (1.0 - s * f);
  t = v * (1.0 - s * (1.0 - f));

  // Determine RGB
  switch (i % 6) {
    case 0: r = trunc(v * 255); g = trunc(t * 255); b = trunc(p * 255); break;
    case 1: r = trunc(q * 255); g = trunc(v * 255); b = trunc(p * 255); break;
    case 2: r = trunc(p * 255); g = trunc(v * 255); b = trunc(t * 255); break;
    case 3: r = trunc(p * 255); g = trunc(q * 255); b = trunc(v * 255); break;
    case 4: r = trunc(t * 255); g = trunc(p * 255); b = trunc(v * 255); break;
    case 5: r = trunc(v * 255); g = trunc(p * 255); b = trunc(q * 255); break;
  }

  return 0xFF000000 | (r << 16) | (g << 8) | b;
}

double frac(const double value) {
  return std::modf(value, nullptr);
}

export void init() {
  initBuffer();
}

export void afterInit() {
  writeLog("Hello from hello_minimal!");
}

export void update() {
  t++;
}

export void draw() {
  cls(0xFF6495ED);

  for (Word a = 0; a < vgaWidth; a++)
    vline(a, 0, vgaHeight - 1,
      HSVtoRGB(frac((double)(a + t) / vgaWidth), 1.0, 1.0));

  vgaFlush();
}
