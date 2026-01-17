"use strict";

class Game extends Posit92 {

}

const TargetFPS = 60;
const FrameTime = 1000 / TargetFPS;

/**
 * in milliseconds
 */
let lastFrameTime = 0.0;

let done = false;

/**
 * Entry point
 */
async function main() {
  const game = new Game("game");
  await game.init();

  game.wasmInstance.exports.setImgCGA8x8(
    await game.loadImage("assets/images/CGA8x8.png"));
  
  game.hideLoadingOverlay();
  game.wasmInstance.exports.afterInit();

  function loop(currentTime) {
    if (done) {
      game.cleanup();
      return
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

function play() {
  const overlay = document.getElementById("play-overlay");
  overlay.parentNode.removeChild(overlay);

  main()
}
