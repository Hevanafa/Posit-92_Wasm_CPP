const importObject = {
  env: {
    // Emscripten
    emscripten_notify_memory_growth: (memoryIndex) => {},
    vgaFlush: () => {
      const surfacePtr = this.#wasm.exports.getSurfacePtr();
      const imageData = new Uint8ClampedArray(
        this.#wasm.exports.memory.buffer,
        surfacePtr,
        this.#vgaWidth * this.#vgaHeight * 4
      );

      const imgData = new ImageData(imageData, this.#vgaWidth, this.#vgaHeight);

      this.#ctx.putImageData(imgData, 0, 0);
    }
  }
}

mergeInto(LibraryManager.library, {
  vgaFlush: () => {
    importObject.env.vgaFlush()
  }
})