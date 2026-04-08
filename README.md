# QR Decoder
- A very simple, standalone QR decoder for my personal use. The only thing it can do is read QR-codes from images.
- Made using [quirc](https://github.com/dlbeer/quirc) and [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h).
## Requirements
- CMake Version 3.28+
- C++17 compatible compiler

## Build Instructions
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
## Usage
```shell
./build/qr-decoder <path_to_image>
```
