/**
 * This file is only required during compile time
 */

"use strict";

mergeInto(LibraryManager.library, {
  signalDone: () => {},
  vgaFlush: () => {}
})
