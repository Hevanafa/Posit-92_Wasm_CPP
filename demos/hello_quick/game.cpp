#include <emscripten.h>
#include <stdint.h>
#include <math.h>

#include "pascal_compat.hpp"
#include "vga.hpp"
#include "keyboard.hpp"
#include "graphics.hpp"
#include "mouse.hpp"
#include "timing.hpp"
#include "loading.hpp"
#include "img_ref.hpp"
#include "img_ref_fast.hpp"
#include "logger.hpp"
#include "fps.hpp"
#include "wasm_heap.hpp"
#include "bmfont.hpp"
#include "fullscreen.hpp"

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
  extern void hideLoadingOverlay();
  extern void loadAssets();
}

void drawFPS() {
  printDefault("FPS:" + i32str(getLastFPS()), 240, 0);
}

void drawMouse() {
  spr(imgCursor, mouseX, mouseY);
}

export void beginLoadingState() {
  actualGameState = GameStateLoading;
  fitCanvas();
  loadAssets();
}

void beginPlayingState() {
  hideCursor();
  fitCanvas();

  // Initialise game state here
  actualGameState = GameStatePlaying;
  gameTime = 0.0;
}

void renderLoadingScreen() {
  std::string s;
  Word w;

  cls(0xFF000000);

  s = "Progress: " + i32str(getLoadingActual()) + " / " + i32str(getLoadingTotal());
  w = measureDefault(s);
  printDefault(s, (vgaWidth - w) / 2, vgaHeight / 2 - defaultFont.lineHeight);

  vgaFlush();
}


export void cleanup() {
  
}

export void init() {
  initBuffer();
  initDeltaTime();
  initFPSCounter();
}

export void afterInit() {
  beginPlayingState();
}

export void update() {
  updateDeltaTime();
  incrementFPS();

  // Handle inputs
  updateMouse();

  if (isKeyDown(SC_ESC)) signalDone();

  // Update your game state here
  gameTime += dt;
}

export void draw() {
  Word w;
  std::string s;

  if (actualGameState == GameStateLoading) {
    renderLoadingScreen();
    return;
  }

  cls(CornflowerBlue);

  if (((LongInt)(gameTime * 4) & 1) > 0)
    spr(imgDosuEXE[1], 148, 88);
  else
    spr(imgDosuEXE[0], 148, 88);

  s = "Hello world!";
  w = measureDefault(s);
  printDefault("Hello world!", 30, 30);

  drawMouse();
  drawFPS();
  vgaFlush();
}
