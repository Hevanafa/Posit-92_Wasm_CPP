/**
 * This file is only required during compile time
 * 
 * See game.js for the implementation
 */

"use strict";

mergeInto(LibraryManager.library, {
  signalDone: () => {},
  isKeyDown: (n) => {},
  vgaFlush: () => {}
})
