cmake_minimum_required(VERSION 3.16)

project(qr-decoder CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(zxing-cpp CONFIG QUIET)

if(NOT zxing-cpp_FOUND)
    include(FetchContent)
    
    FetchContent_Declare(
        zxing-cpp
        URL https://github.com/zxing-cpp/zxing-cpp/archive/refs/tags/v2.2.1.zip
        URL_HASH sha256:9df8ffdd9330836714440b6f9c5bab3681a918d84aac6c0bcbab00bda86bc228
    )
    
    FetchContent_MakeAvailable(zxing-cpp)
endif()

set(ZXING_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

add_executable(qr-decoder src/main.cpp)

target_include_directories(qr-decoder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)

target_link_libraries(qr-decoder PRIVATE ZXing::ZXing)
