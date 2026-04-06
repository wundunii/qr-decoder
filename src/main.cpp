#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <ReadBarcode.h>

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
  int in_channels = 0;
  int out_channels = 1; // 1 = Grayscale

  // unsigned char is 1 byte = a pixel's color value 0-255
  unsigned char* data = stbi_load(argv[1], &width, &height, &in_channels, out_channels);

  if (data == nullptr) {
    std::cerr << "Error: Could not load image.\n"
              << "Reason: " << stbi_failure_reason() << std::endl;
    return 2;
  }

  std::cout << "Image successfully loaded.\n";

  try {
    //Create ImageView (throw if dimensions are invalid)
    ZXing::ImageView img{data, width, height, ZXing::ImageFormat::Lum};

    //Decode (throw if mem alloc fails)
    auto barcodes = ZXing::ReadBarcodes(img);

    if (barcodes.empty()) {
      std::cout << "Could not find QR code." << std::endl;
    } else {
      std::cout << "-----------------------------\n" << "Result:" << std::endl;
      for (const auto& barcode : barcodes) {
        std::cout << barcode.text() << std::endl;
      }
    }
  }
  catch (const std::exception& e) {
    std::cerr << "A fatal exception occurred during decoding: " << e.what() << std::endl;
  }
  catch (...) {
    std::cerr << "An unknown error occurred!" << std::endl;
  }

  stbi_image_free(data);

  return 0;
}
