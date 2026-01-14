
C++ subset port of my [Posit-92 Wasm](https://github.com/Hevanafa/Posit-92_Wasm) game engine

The glue code is based on `hello_quick` demo, so it's experimental

## Emscripten Setup

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
