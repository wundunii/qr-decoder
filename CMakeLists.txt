cmake_minimum_required(VERSION 3.28)

project(qr-decoder LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Populate(
  quirc
  URL https://github.com/dlbeer/quirc/archive/refs/heads/master.zip
  SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/quirc
)

set(QUIRC_SOURCES
  ${CMAKE_CURRENT_BINARY_DIR}/quirc/lib/quirc.c
  ${CMAKE_CURRENT_BINARY_DIR}/quirc/lib/decode.c
  ${CMAKE_CURRENT_BINARY_DIR}/quirc/lib/identify.c
  ${CMAKE_CURRENT_BINARY_DIR}/quirc/lib/version_db.c
)

add_executable(qr-decoder src/main.cpp ${QUIRC_SOURCES})

target_include_directories(qr-decoder PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/quirc/lib)
target_include_directories(qr-decoder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)

if(WIN32)
    set_target_properties(qr-decoder PROPERTIES WIN32_EXECUTABLE TRUE)

    target_link_libraries(qr-decoder PRIVATE user32 shell32 gdi32)

    if(MINGW)
        target_link_options(qr-decoder PRIVATE 
            -static-libgcc 
            -static-libstdc++ 
            -static
        )
    endif()
    
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
endif()
