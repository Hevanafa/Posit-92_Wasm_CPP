#

C++ subset port of my [Posit-92 Wasm](https://github.com/Hevanafa/Posit-92_Wasm) game engine

The glue code is based on `hello_quick` demo, so it's experimental

## Requirements

1. Emscripten
2. VSCode (or any text editor that supports editing C++ code)
3. [Bun](https://bun.com/) for build scripts

I'm using a Windows 110 machine to compile & run this project

## Setup & Installation

### Emscripten Setup

1. Install Emscripten

   I installed Emscripten in `E:`, so `emsdk` will be available in `E:\emsdk`

   ```powershell
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   
   .\emsdk.ps1 install latest
   .\emsdk.ps1 activate latest
   ```

2. Add Emscripten to PATH

   It's either done by `emsdk_env.ps1` or by manually adding the installation path in the Environment Variables

3. Test if Emscripten actually works

   ```powershell
   emcc --version
   ```

It should output along these lines:

```text
emcc (Emscripten gcc/clang-like replacement + linker emulating GNU ld) 3.1.73 (ac676d5e437525d15df5fd46bc2c208ec6d376a3)
Copyright (C) 2014 the Emscripten authors (see AUTHORS.txt)
```

### Microsoft's C++ Extension Setup for VSCode

1. Install this one: [C/C++ by Microsoft](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

2. Add this in the `includePath`:

   ```powershell
   E:\emsdk\upstream\emscripten\cache\sysroot\include
   ```

   The path depends on where you installed `emsdk`

## Workflow in General

The workflow that I use is different. It's much simpler from Emscripten's default way of doing

I chose this approach because it gives me more control & minimal bloat -- only less than 1 KB instead of Emscripten's default glue code, which is around 50 KB

## Project Structure

The prototype version has a few key files:
- **game.cpp** - The primary file / entry point
- **game.js**
  This contains the bare minimum to get WebAssembly running, which you can scroll down to find `init()`
- index.html
- library.js

Also the build scripts:
- compile.ts
- run.ts
- server.ts