# QR Decoder
- A very simple, standalone QR decoder for my personal use. The only thing it can do is read QR-codes from images.
- Made using [quirc](https://github.com/dlbeer/quirc) and [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h).
## How to use:
### Windows:
- Download qr-decoder-windows.exe in [Releases](https://github.com/wundunii/qr-decoder/releases).
- Drag and drop image onto the file.
- Result will be showed and also copied to your clipboard automatically.
### Linux:
- Download qr-decoder-linux in [Releases](https://github.com/wundunii/qr-decoder/releases).
- Run via terminal:
```
./qr-decoder-linux <path_to_image>
```
## Build Instructions
### Requirements
- CMake Version 3.28+
- C++17 compatible compiler
### Linux
```shell
cmake -B build

cmake --build build
```
### Windows
```shell
cmake -B build -G <compiler>
#Example: cmake -B build -G "MinGW Makefiles"

cmake --build build
```
