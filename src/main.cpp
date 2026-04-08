#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "quirc.h"

int main(int argc, char* argv[]) {
  std::cout << "Initializing QR Decoder..." << std::endl;

  if(argc != 2) {
    std::cerr << "Error: you must provide an image path." << std::endl;
    std::cerr << "Usage: ./qr-decoder <path_to_image>" << std::endl;
    return 1;
  }
  
  std::cout << "Loading image: " << argv[1] << std::endl;

  int width = 0;
  int height = 0;
  int channels = 0;

  // unsigned char is 1 byte = a pixel's color value 0-255
  unsigned char* pixels = stbi_load(argv[1], &width, &height, &channels, STBI_grey);

  if (pixels == nullptr) {
    std::cerr << "Error: Could not load image.\n"
              << "Reason: " << stbi_failure_reason() << std::endl;
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

  for (int i = 0; i < res_count; i++) {
    struct quirc_code code;
    struct quirc_data data;
    
    quirc_extract(q, i, &code);

    quirc_decode_error_t err = quirc_decode(&code, &data);

    if (err != QUIRC_SUCCESS) {
      std::cerr << "Decoding failed: " << quirc_strerror(err) << std::endl;
    } else {
      std::cout << "--------------------\nResult:\n" << data.payload << std::endl;
    }
  }

  quirc_destroy(q);
  stbi_image_free(pixels);

  return 0;
}
