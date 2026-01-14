"use strict";

const vgaWidth = 320, vgaHeight = 200;

const canvasID = "game";
const wasmSource = "game.wasm";

let wasm = null;
/**
 * @type {HTMLCanvasElement}
 */
let canvas;
let ctx;

const importObject = {
  env: {
    // Emscripten
    emscripten_notify_memory_growth: (memoryIndex) => {},

    vgaFlush: () => {
      const surfacePtr = wasm.exports.getSurfacePtr();
      const imageData = new Uint8ClampedArray(
        wasm.exports.memory.buffer,
        surfacePtr,
        vgaWidth * vgaHeight * 4
      );

      const imgData = new ImageData(imageData, vgaWidth, vgaHeight);

      ctx.putImageData(imgData, 0, 0);
    }
  }
}

async function initWebAssembly() {
  const response = await fetch(wasmSource);
  const result = WebAssembly.instantiate(response.buffer, importObject);
  wasm = result.instance
}

// Library
mergeInto(LibraryManager.library, {
  vgaFlush: () => {
    importObject.env.vgaFlush()
  }
})

// Entry point
canvas = document.getElementById(canvasID);
if (canvas == null)
  throw new Error(`Couldn't find canvasID \"${ canvasID }\"`);

ctx = canvas.getContext("2d");
