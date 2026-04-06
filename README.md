# QR Decoder
- A very simple, standalone QR decoder for my personal use. The only thing it can do is read QR-codes from images.
- Made using [ZXing-cpp](https://github.com/zxing-cpp/zxing-cpp) and [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h).
## Requirements
- CMake Version 3.16+
- C++20 compatible compiler: GCC v11+, Clang v14+, MSVC Visual Studio 2022 (v17+),...

## Build Instructions
```shell
cmake -B build
cmake --build build
```
## Usage
```shell
./build/qr-decoder <path_to_image>
```
