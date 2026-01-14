"use strict";

class Game {
  ScancodeMap = {
    "Escape": 0x01
    // Add more scancodes as necessary
  };

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

      isKeyDown: this.#isKeyDown.bind(this),
      signalDone: this.#signalDone.bind(this),

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

    this.#initKeyboard();
    // this.#initMouse();
  }

  #assertString(value) {
    if (typeof value != "string")
      throw new Error(`Expected a string, but received ${typeof value}`);
  }

  afterInit() {
    this.#wasm.exports.afterInit();
  }

  /**
   * Called when `done` is `true`
   */
  cleanup() {
    console.log("cleanup")
    // this.#showCursor();
  }

  // KEYBOARD.PAS
  heldScancodes = new Set();

  #initKeyboard() {
    const ScancodeMap = this.ScancodeMap;
    
    window.addEventListener("keydown", e => {
      if (e.repeat) return;

      const scancode = ScancodeMap[e.code];
      if (scancode) {
        this.heldScancodes.add(scancode);
        e.preventDefault();
      }
    })

    window.addEventListener("keyup", e => {
      const scancode = ScancodeMap[e.code];
      if (scancode) this.heldScancodes.delete(scancode)
    })
  }

  #isKeyDown(scancode) {
    return this.heldScancodes.has(scancode)
  }

  #signalDone() {
    done = true
  }

  // vga.hpp
  #vgaFlush() {
    // console.log("vgaFlush");

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

const TargetFPS = 60;
const FrameTime = 1000 / 60.0;
/**
 * in milliseconds
 */
let lastFrameTime = 0.0;

var done = false;

async function main() {
  const game = new Game("game");
  await game.init();
  game.afterInit();

  function loop(currentTime) {
    if (done) {
      game.cleanup();
      return;
    }

    const elapsed = currentTime - lastFrameTime;

    if (elapsed >= FrameTime) {
      lastFrameTime = currentTime - (elapsed % FrameTime);  // Carry over extra time
      game.update();
      game.draw();
    }

    requestAnimationFrame(loop)
  }

  requestAnimationFrame(loop)
}

// Entry point
function play() {
  main()
}
