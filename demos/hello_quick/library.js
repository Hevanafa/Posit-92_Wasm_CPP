/**
 * This file is only required during compile time
 * 
 * See game.js for the implementation
 */

"use strict";

mergeInto(LibraryManager.library, {
  // Intro
  hideLoadingOverlay: () => {},
  loadAssets: () => {},

  // Loading
  getLoadingActual: () => {},
  getLoadingTotal: () => {},

  hideCursor: () => {},
  showCursor: () => {},

  // Fullscreen
  toggleFullscreen: () => {},
  endFullscreen: () => {},
  getFullscreenState: () => {},
  fitCanvas: () => {},

  // keyboard.hpp
  isKeyDown: (n) => {},
  signalDone: () => {},

  // logger.hpp
  writeLogF32: n => {},
  writeLogI32: n => {},
  writeLogI64: n => {},
  flushLog: () => {},

  // Mouse
  getMouseX: () => {},
  getMouseY: () => {},
  getMouseButton: () => {},

  // panic.hpp
  jsPanicHalt: (a, b) => {},

  // timing.hpp
  getTimer: () => {},
  getFullTimer: () => {},

  // vga.hpp
  vgaFlush: () => {}
});
