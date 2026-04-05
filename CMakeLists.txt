cmake_minimum_required(VERSION 3.16)

project(QR-decoder CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  zxing-cpp
  GIT_REPOSITORY  https://github.com/zxing-cpp/zxing-cpp.git
  GIT_TAG 8dd1cf5c4fd6fb6211bb96713db926ac6f2cf825 #VERSION 3.0.2
)

set(ZXING_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(zxing-cpp)

add_executable(QR-decoder src/main.cpp)

target_include_directories(QR-decoder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)

target_link_libraries(QR-decoder PRIVATE ZXing::ZXing)
