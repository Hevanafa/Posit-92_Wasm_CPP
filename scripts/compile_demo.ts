import { styleText } from "node:util";
import { exportedFunctions } from "./exported";

const compilerPath = "E:\\emsdk\\upstream\\emscripten\\emcc.bat";
const primaryFile = ".\\game.cpp";
const outputFile = "game.wasm";

const commandLine = [
  compilerPath,
  primaryFile,
  "-o", outputFile,
  "-I..\\..\\experimental\\includes",
  "-s", "STANDALONE_WASM=1",
  "-s", "STACK_SIZE=256000",
  "-s", `EXPORTED_FUNCTIONS=${ exportedFunctions.map(fname => `_${fname}`).join(",") }`,
  "--js-library", "library.js",
  "--no-entry"
];

const proc = Bun.spawn(commandLine, {
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
