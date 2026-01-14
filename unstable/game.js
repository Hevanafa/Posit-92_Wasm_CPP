"use strict";

class Game {

  #wasmSource = "game.wasm";

  #vgaWidth = 320;
  #vgaHeight = 200;

  /**
   * @type {HTMLCanvasElement}
   */
  #canvas;
  /**
   * @type {CanvasRenderingContext2D}
   */
  #ctx;

  /**
   * @type {WebAssembly.Instance}
   */
  #wasm;

  #importObject = {
    env: {
      // Emscripten
      emscripten_notify_memory_growth: (memoryIndex) => {},

      vgaFlush: this.#vgaFlush.bind(this)
    }
  }

  constructor(canvasID) {
    if (canvasID == null)
      throw new Error("canvasID is required!");

    this.#assertString(canvasID);

    this.#canvas = document.getElementById(canvasID);
    if (this.#canvas == null)
      throw new Error(`Couldn't find canvasID \"${ canvasID }\"`);

    this.#ctx = this.#canvas.getContext("2d");
  }

  async #initWebAssembly() {
    console.log("initWebAssembly");

    const response = await fetch(this.#wasmSource);
    const bytes = await response.arrayBuffer();
    const result = await WebAssembly.instantiate(bytes, this.#importObject);
    this.#wasm = result.instance;

    console.log("wasm?", this.#wasm);
  }

  async init() {
    await this.#initWebAssembly();
    this.#wasm.exports.init();
  }

  #assertString(value) {
    if (typeof value != "string")
      throw new Error(`Expected a string, but received ${typeof value}`);
  }

  afterInit() {
    this.#wasm.exports.afterInit();
  }

  // vga.hpp
  #vgaFlush() {
    console.log("vgaFlush");

    const surfacePtr = this.#wasm.exports.getSurfacePtr();
    const imageData = new Uint8ClampedArray(
      this.#wasm.exports.memory.buffer,
      surfacePtr,
      this.#vgaWidth * this.#vgaHeight * 4
    );

    const imgData = new ImageData(imageData, this.#vgaWidth, this.#vgaHeight);

    this.#ctx.putImageData(imgData, 0, 0);
  }

  update() { this.#wasm.exports.update(); }
  draw() { this.#wasm.exports.draw(); }
}

async function main() {
  const game = new Game("game");
  await game.init();
  game.afterInit();

  game.draw();
}

// Entry point
function play() {
  main()
}
