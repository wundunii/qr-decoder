#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "quirc.h"
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>

void CopyToClipboard(const std::string& s) {
    if (!OpenClipboard(NULL)) return;
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!hg) {
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
}

void ShowWindowsResult(const std::string& result) {
    std::string message = "Result (Copied to clipboard):\n\n" + result;
    MessageBoxA(NULL, message.c_str(), "QR Decoder Result", MB_OK | MB_ICONINFORMATION);
}
#endif

int main(int argc, char* argv[]) {
  std::cout << "Initializing QR Decoder..." << std::endl;

  if(argc != 2) {
    #ifdef _WIN32
      MessageBoxA(NULL, "Please drag an image file onto this .exe to decode it.", "How to use", MB_OK);
    #else
      std::cerr << "Error: you must provide an image path." << std::endl;
      std::cerr << "Usage: ./qr-decoder <path_to_image>" << std::endl;
    #endif
    return 1;
  }
  
  std::cout << "Loading image: " << argv[1] << std::endl;

  int width = 0;
  int height = 0;
  int channels = 0;

  // unsigned char is 1 byte = a pixel's color value 0-255
  unsigned char* pixels = stbi_load(argv[1], &width, &height, &channels, STBI_grey);

  if (pixels == nullptr) {
    #ifdef _WIN32
      std::string stbi_err = std::string("Error: Could not load image.\nReason: ") + stbi_failure_reason();
      MessageBoxA(NULL, stbi_err.c_str(), "Error", MB_ICONERROR);
    #else
      std::cerr << "Error: Could not load image.\nReason: " << stbi_failure_reason() << std::endl;
    #endif
    return 2;
  }

  std::cout << "Image successfully loaded.\n";

  // Init quirc and alloc its internal memory
  struct quirc* q = quirc_new();
  quirc_resize(q, width, height);

  // Pointer to quirc's internal buffer
  int q_width, q_height;
  uint8_t* quirc_buffer = quirc_begin(q, &q_width, &q_height);

  memcpy(quirc_buffer, pixels, width * height);

  // Done loading data
  quirc_end(q);

  int res_count = quirc_count(q);
  std::cout << "Found " << res_count << " QR codes." << std::endl;

  std::string all_results = "";

  for (int i = 0; i < res_count; i++) {
    struct quirc_code code;
    struct quirc_data data;
    
    quirc_extract(q, i, &code);

    quirc_decode_error_t err = quirc_decode(&code, &data);

    if (err != QUIRC_SUCCESS) {
      all_results += "QR Code " + std::to_string(i + 1) + " Error: ";
      all_results += quirc_strerror(err);
      all_results += "\n";
    } else {
      all_results += (const char*)data.payload;
      all_results += "\n";
    }

    if (!all_results.empty()) {
      #ifdef _WIN32
        CopyToClipboard(all_results);
        ShowWindowsResult(all_results);
      #else
        std::cout << "--------------------\nResult:\n" << data.payload << std::endl;
      #endif
    }
  }


  quirc_destroy(q);
  stbi_image_free(pixels);

  return 0;
}
