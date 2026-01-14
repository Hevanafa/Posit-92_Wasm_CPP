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
  get wasmInstance() { return this.#wasm }

  /**
   * Used in getTimer
   */
  #midnightOffset = 0;

  #importObject = {
    env: {
      // Emscripten
      emscripten_notify_memory_growth: (memoryIndex) => {},

      isKeyDown: this.#isKeyDown.bind(this),
      signalDone: this.#signalDone.bind(this),

      // Timing
      getTimer: () => this.#getTimer(),
      getFullTimer: () => this.#getFullTimer(),

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

  #loadMidnightOffset() {
    const now = new Date();
    const midnight = new Date(now.getFullYear(), now.getMonth(), now.getDate());
    this.#midnightOffset = midnight.getTime()
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
    this.#loadMidnightOffset();

    Object.freeze(this.#importObject);
    await this.#initWebAssembly();
    this.#wasm.exports.init();

    this.#initKeyboard();
    // this.#initMouse();
  }

  #assertString(value) {
    if (typeof value != "string")
      throw new Error(`Expected a string, but received ${typeof value}`);
  }


  async loadImageFromURL(url) {
    if (url == null)
      throw new Error("loadImageFromURL: url is required");

    this.#assertString(url);

    return new Promise((resolve, reject) => {
      const img = new Image();
      img.onload = () => resolve(img);
      img.onerror = reject;
      img.src = url
    })
  }

  // Used in loadImage
  #images = [];

  async loadImage(url) {
    if (url == null)
      throw new Error("loadImage: url is required");

    this.#assertString(url);

    const img = await this.loadImageFromURL(url);

    // Copy image
    const tempCanvas = document.createElement("canvas");
    tempCanvas.width = img.width;
    tempCanvas.height = img.height;
    const tempCtx = tempCanvas.getContext("2d");
    tempCtx.drawImage(img, 0, 0);

    const imageData = tempCtx.getImageData(0, 0, img.width, img.height);

    const wasmMemory = new Uint8Array(this.#wasm.exports.memory.buffer);
    const byteSize = img.width * img.height * 4;
    const wasmPtr = this.#wasm.exports.WasmGetMem(byteSize);
    wasmMemory.set(imageData.data, wasmPtr)

    if (this.#images.length == 0)
      this.#images.push(null);

    // Register with Wasm pointer
    const handle = this.#images.length;
    this.#images.push(imageData);  // Keep data in JS for reference
    this.#wasm.exports.registerImageRef(handle, wasmPtr, img.width, img.height);

    return handle
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

  // timing.hpp
  #getTimer() {
    return (Date.now() - this.#midnightOffset) / 1000
  }

  #getFullTimer() {
    return Date.now() / 1000
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

  async loadAssets() {
    let handle = 0;

    handle = await this.loadImage("assets/images/8x8.png");
    this.wasmInstance.exports.setImgCGA8x8(handle);
  }
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
  await game.loadAssets();
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
