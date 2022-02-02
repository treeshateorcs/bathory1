#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "convert_to.hpp"
#include "fmt/core.h"
#include "qoi.h"
#include "stb_image_write.h"
#include <fstream>

void convert_from_intermediary_to_qoi(BYTE *output_buffer, std::size_t *len,
                                      qoi_desc *desc,
                                      const std::string &output_filename) {
  int encoded = qoi_write(output_filename.c_str(), output_buffer, desc);
  if (!encoded) {
    fmt::print("Couldn't write/encode\n");
    exit(1);
  }
}

void convert_from_intermediary_to_bmp(BYTE *output_buffer, std::size_t *len,
                                      qoi_desc *desc,
                                      const std::string &output_filename) {
  int res = stbi_write_bmp(output_filename.c_str(), desc->width, desc->height,
                           4, output_buffer);
  if (res) {
    fmt::print("Couldn't write/encode\n");
    exit(1);
  }
}

void convert_from_intermediary_to_tga(BYTE *output_buffer, std::size_t *len,
                                      qoi_desc *desc,
                                      const std::string &output_filename) {
  int res = stbi_write_tga(output_filename.c_str(), desc->width, desc->height,
                           4, output_buffer);
  if (res) {
    fmt::print("Couldn't write/encode: error {}\n", res);
    exit(1);
  }
}

void convert_from_intermediary_to_jpeg(BYTE *output_buffer, std::size_t *len,
                                       qoi_desc *desc,
                                       const std::string &output_filename) {
  int res = stbi_write_jpg(output_filename.c_str(), desc->width, desc->height,
                           4, output_buffer, 50);
  if (res) {
    fmt::print("Couldn't write/encode\n");
    exit(1);
  }
}

void convert_from_intermediary_to_png(BYTE *output_buffer, std::size_t *len,
                                      qoi_desc *desc,
                                      const std::string &output_filename) {
  int res = stbi_write_png(output_filename.c_str(), desc->width, desc->height,
                           4, output_buffer, desc->width * 4);
  if (res) {
    fmt::print("Couldn't write/encode\n");
    exit(1);
  }
}
