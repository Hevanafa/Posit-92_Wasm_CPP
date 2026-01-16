import { styleText } from "node:util";

const compilerPath = "E:\\emsdk\\upstream\\emscripten\\emcc.bat";

const proc = Bun.spawn([
  compilerPath,
  "--clear-cache"
], {
  stdout: "pipe",
  stderr: "pipe"
});

const stdout = await new Response(proc.stdout).text();
const stderr = await new Response(proc.stderr).text();

console.log(styleText("cyan", "(STDOUT)"));
console.log(stdout.trim() || styleText("gray", "(No data)"));

console.log(styleText("red", "(STDERR)"));
console.log(stderr.trim() || styleText("gray", "(No data)"));

export {}
