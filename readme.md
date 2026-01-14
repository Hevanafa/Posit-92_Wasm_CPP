#

C++ subset port of my [Posit-92 Wasm](https://github.com/Hevanafa/Posit-92_Wasm) game engine

The glue code (not prototype) is based on `hello_quick` demo, so it's experimental

## Workflow in General

The workflow that I use is different. It's much simpler from Emscripten's default way of doing

I chose this approach because it gives me more control & minimal bloat -- only less than 1 KB instead of Emscripten's default glue code, which is around 50 KB

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

## Project Structure

The **prototype** version has a few key files:

- **game.cpp**
  
  The primary file / entry point

  `export` is actually a macro, not a bareword

- **game.js**
  
  This contains the bare minimum to get WebAssembly running, which you can scroll down to find `init()`

- **index.html**
  
  The HTML entry point, which calls `init()` in **game.js**

- **library.js**
  
  This contains stub functions, which are used only during compile time. You can make sure that the functions with the same name are available in `game.cpp`, which have `extern void` in the signature
  
  These functions are used to trick the compiler into thinking that the actual implementation is available from it, but those functions are actually available in `importObject`, which is accessible from WebAssembly instantiation

Also the build scripts:

- **compile.ts** - Compiles `game.cpp` to `game.wasm`
- **run.ts** - Calls `server.ts`
- **server.ts** - A basic server code that starts on `localhost:8008`

## About the Compilation Process

### `emcc` Command Breakdown

The full command line looks like this:

```powershell
E:\emsdk\upstream\emscripten\emcc.bat .\game.cpp -o game.wasm -s STANDALONE_WASM=1 -s EXPORTED_FUNCTIONS=_getSurfacePtr,_init,_update,_draw,_cleanup --js-library library.js --no-entry
```

- `E:\emsdk\upstream\emscripten\emcc.bat` is the complete path of `emcc`
- `.\game.cpp` - this is the primary file / entry point
- `-o game.wasm`
  
  This makes a WASM binary output, which is expected.
  
  But, if you want to see how the default Emscripten glue code looks like by default, use `.js` extension for it, e.g. `game.js`

- `-s STANDALONE_WASM=1` - this makes it a standalone WebAssembly binary without the entry point `main()`
- `-s EXPORTED_FUNCTIONS`

  You can list the exported functions from C++ here, just add an underscore prefix on each item so that the compiler won't complain

  Every exported function has the `extern "C" EMSCRIPTEN_KEEPALIVE` prefix so that it doesn't get deleted during compile time **and** doesn't get its name mangled

- `--js-library library.js` - this contains the stub function declarations
- `--no-entry` - this makes it not call `main()` since it's technically a WebAssembly *library*

### Why do I need stub declarations?

In Pascal, when I want to call a JS function, I can simply use this syntax:

```pascal
procedure signalDone; external 'env' name 'signalDone';
function getTimer: double; external 'env' name 'getTimer';
```

But with Emscripten (C++), I should use its mechanism willy-nilly, in order to be able to reuse my glue code from Posit-92 Wasm.  This approach is better than having to write inline JS for everything


