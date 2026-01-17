#include <emscripten.h>
#include <stdint.h>
#include <math.h>

#include "pascal_compat.hpp"
#include "vga.hpp"
#include "keyboard.hpp"
#include "graphics.hpp"
#include "timing.hpp"
#include "img_ref.hpp"
#include "img_ref_fast.hpp"
#include "logger.hpp"
#include "fps.hpp"
#include "wasm_heap.hpp"
#include "bmfont.hpp"

#include "assets.hpp"

extern "C" {
  extern void signalDone();
}

enum TGameStates {
  GameStateIntro = 1,
  GameStateLoading = 2,
  GameStatePlaying = 3
};

const Byte
  SC_ESC = 0x01;

const LongWord CornflowerBlue = 0xFF6495ED;

// Game state variables
TGameStates actualGameState;
double gameTime;

extern "C" {
  extern void signalDone();
  extern void hideCursor();
  extern void hideLoadingOverlay();
  extern void loadAssets();
}

void drawFPS() {
  printDefault("FPS:" + i32str(getLastFPS()), 240, 0);
}


export void cleanup() {
  
}

export void init() {
  initBuffer();
  initDeltaTime();
  initFPSCounter();
}

export void afterInit() {
  gameTime = 0.0;
}

export void update() {
  updateDeltaTime();
  incrementFPS();

  if (isKeyDown(SC_ESC)) signalDone();

  // Update your game state here
  gameTime += dt;
}

export void draw() {
  double x, y;

  cls(CornflowerBlue);

  printBMFont(defaultFont, defaultFontGlyphs, "Hello world!", 30, 30);

  drawFPS();
  vgaFlush();
}
