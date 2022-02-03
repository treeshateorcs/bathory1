#include "convert_from.hpp"
#include "format.hpp"
#include "identify.hpp"
#include "qoi.h"
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_LINEAR
#include "stb_image.h"

void determine_output_format(std::string &output_extension,
                             Format &output_format) {
  auto n = output_extension.rfind(".");
  output_extension = output_extension.substr(n + 1);
  if (output_extension == "gif") {
    output_format = Format::gif;
  } else if (output_extension == "qoi") {
    output_format = Format::qoi;
  } else if (output_extension == "bmp") {
    output_format = Format::bmp;
  } else if (output_extension == "tga") {
    output_format = Format::tga;
  } else if (output_extension == "png") {
    output_format = Format::png;
  } else if (output_extension == "jpeg" || output_extension == "jpg") {
    output_format = Format::jpeg;
  } else {
    output_format = Format::unknown;
  }
}
void convert_qoi_to_intermediary(const std::vector<BYTE> &i, BYTE **o,
                                 std::size_t len, qoi_desc *desc) {
  *o = reinterpret_cast<BYTE *>(qoi_decode(&i[0], len, desc, 4));
  if (*o == nullptr) {
    fmt::print("failed decoding\n");
    std::exit(EXIT_FAILURE);
  }
}

void convert_to_intermediary(const std::vector<BYTE> &i, BYTE **o,
                             std::size_t len, qoi_desc *desc) {
  if (!stbi_info_from_memory(&i[0], i.size(),
                             reinterpret_cast<int *>(&desc->width),
                             reinterpret_cast<int *>(&desc->height),
                             reinterpret_cast<int *>(&desc->channels))) {
    fmt::print("Couldn't read header\n");
    std::exit(1);
  }
  if (desc->channels != 3) {
    desc->channels = 4;
  }
  *o = stbi_load_from_memory(
      &i[0], i.size(), reinterpret_cast<int *>(&desc->width),
      reinterpret_cast<int *>(&desc->height), nullptr, desc->channels);
  if (*o == nullptr) {
    fmt::print("Couldn't load/decode\n");
    std::exit(1);
  }
  desc->colorspace = QOI_SRGB;
}
