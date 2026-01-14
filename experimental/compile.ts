import { styleText } from "node:util";

const compilerPath = "E:\\emsdk\\upstream\\emscripten\\emcc.bat";
const primaryFile = ".\\game.cpp";
const outputFile = "game.wasm";

const exportedFunctions = ["getSurfacePtr", "init", "update", "draw", "cleanup"];

const proc = Bun.spawn([
  compilerPath,
  primaryFile,
  "-o", outputFile,
  "-s", "STANDALONE_WASM=1",
  "-s", `EXPORTED_FUNCTIONS=${ exportedFunctions.map(fname => `_${fname}`).join(", ") }`,
  "-s", "ALLOW_MEMORY_GROWTH=1",
  "--js-library", "library.js",
  "--no-entry"
  // "-o", "example.js"
], {
  stdout: "pipe",
  stderr: "pipe"
});

const stdout = await new Response(proc.stdout).text();
const stderr = await new Response(proc.stderr).text();
const exitCode = await proc.exited;

console.log(styleText("cyan", "(STDOUT)"));
console.log(stdout.trim() || styleText("gray", "(No data)"));

console.log(styleText("red", "(STDERR)"));
console.log(stderr.trim() || styleText("gray", "(No data)"));

if (exitCode != 0) {
  console.log(styleText("red", `Compilation failed with exit code ${exitCode}`));
  process.exit(exitCode)
}

export {}
