/**
 * This file is only required during compile time
 */

"use strict";

mergeInto(LibraryManager.library, {
  signalDone: () => {},
  vgaFlush: () => { console.log("vgaFlush from library!") }
})
