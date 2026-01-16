/**
 * This file is only required during compile time
 * 
 * See game.js for the implementation
 */

"use strict";

mergeInto(LibraryManager.library, {
  signalDone: () => {},

  // keyboard.hpp
  isKeyDown: (n) => {},

  // logger.hpp
  flushLog: () => {},

  // panic.hpp
  jsPanicHalt: (a, b) => {},

  // timing.hpp
  getTimer: () => {},
  getFullTimer: () => {},

  // vga.hpp
  vgaFlush: () => {}
});
