#include "convert_from.hpp"
#include "convert_to.hpp"
#include "format.hpp"
#include "identify.hpp"
#include "stb_image.h"
#include <cstdlib>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define QOI_IMPLEMENTATION
#include "qoi.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::exit(EXIT_FAILURE);
  }
  std::ifstream input{argv[1], std::ios::binary};
  std::array<BYTE, 10> v;
  input.read(reinterpret_cast<char *>(v.data()), 10);
  if (v.size() < 10) {
    std::exit(EXIT_FAILURE);
  }
  input.seekg(0, std::ios::end);
  std::streamsize len = input.tellg();
  input.seekg(0, std::ios::beg);
  std::vector<BYTE> input_buffer(len);
  if (!input.read(reinterpret_cast<char *>(input_buffer.data()), len)) {
    std::exit(1);
  }
  BYTE *output_buffer = nullptr;
  qoi_desc desc{};
  switch (v[0]) {
  case 0x38: // psd
    if (identify_format(v, std::array<BYTE, 4>{0x38, 0x42, 0x50, 0x53})) {
      convert_to_intermediary(input_buffer, &output_buffer, len, &desc);
      break;
    };
  case 0x42: // bmp
    if (identify_format(v, std::array<BYTE, 2>{0x42, 0x4d})) {
      convert_to_intermediary(input_buffer, &output_buffer, len, &desc);
      break;
    };
  case 0x53: // fits
    if (identify_format(
            v, std::array<BYTE, 6>{0x53, 0x49, 0x4d, 0x50, 0x4c, 0x45})) {
      break;
    };
  case 0x47:
    switch (v[1]) {
    case 0x49: // gif
      if (identify_format(v, std::array<BYTE, 4>{0x47, 0x49, 0x46, 0x38})) {
        convert_to_intermediary(input_buffer, &output_buffer, len, &desc);
        break;
      }
    case 0x4b: // gks
      if (identify_format(v, std::array<BYTE, 4>{0x47, 0x4b, 0x53, 0x4d})) {
        break;
      }
    default:
      break;
    }
    break;
  case 0x01: // rgb
    if (identify_format(v, std::array<BYTE, 2>{0x47, 0xda})) {
      break;
    }
  case 0xf1: // itc
    if (identify_format(v, std::array<BYTE, 4>{0xf1, 0x00, 0x40, 0xbb})) {
      break;
    }
  case 0xff: // jpeg
    if (identify_format(v, std::array<BYTE, 4>{0xff, 0xd8, 0xff, 0xe0})) {
      break;
    };
  case 0x49:
    switch (v[2]) {
    case 0x4e: // nif
      if (identify_format(v, std::array<BYTE, 4>{0x49, 0x49, 0x4e, 0x31})) {
        break;
      };
    case 0x2a: // tiff_intel
      if (identify_format(v, std::array<BYTE, 4>{0x49, 0x49, 0x2a, 0x00})) {
        break;
      };
    default:
      break;
    }
    break;
  case 0x56: // pm
    if (identify_format(v, std::array<BYTE, 4>{0x56, 0x49, 0x45, 0x57})) {
      break;
    };
  case 0x89: // png
    if (identify_format(v, std::array<BYTE, 4>{0x89, 0x50, 0x4e, 0x47})) {
      convert_to_intermediary(input_buffer, &output_buffer, len, &desc);
      break;
    };
  case 0x25: // ps
    if (identify_format(v, std::array<BYTE, 2>{0x25, 0x21})) {
      break;
    };
  case 0x59: // ras
    if (identify_format(v, std::array<BYTE, 4>{0x59, 0xa6, 0x6a, 0x95})) {
      break;
    };
  case 0x4d: // tiff_motorola
    if (identify_format(v, std::array<BYTE, 4>{0x4d, 0x4d, 0x00, 0x2a})) {
      break;
    };
  case 0x67: // xcf
    if (identify_format(v,
                        std::array<BYTE, 10>{0x67, 0x69, 0x6d, 0x70, 0x20, 0x78,
                                             0x63, 0x66, 0x20, 0x76})) {
      break;
    };
  case 0x23: // fig
    if (identify_format(v, std::array<BYTE, 4>{0x23, 0x46, 0x49, 0x47})) {
      break;
    };
  case 0x2f: // xpm
    if (identify_format(v, std::array<BYTE, 9>{0x2f, 0x2a, 0x20, 0x58, 0x50,
                                               0x4d, 0x20, 0x2a, 0x2f})) {
      break;
    };
  case 0x71: // qoi
    if (identify_format(v, std::array<BYTE, 4>{0x71, 0x6f, 0x69, 0x66})) {
      convert_qoi_to_intermediary(input_buffer, &output_buffer, len, &desc);
      break;
    };
  default:
    fmt::print("unknown format\n");
    std::exit(EXIT_FAILURE);
  }
  Format output_format{Format::unknown};
  std::string output_extension{argv[2]};
  determine_output_format(output_extension, output_format);
  if (output_format == Format::unknown) {
    fmt::print("format unknown\n");
    std::exit(EXIT_FAILURE);
  }
  switch (output_format) {
  case Format::bmp:
    convert_from_intermediary_to_bmp(output_buffer, len, &desc, argv[2]);
    break;
  case Format::fits:
  case Format::gif:
  case Format::gks:
  case Format::rgb:
  case Format::itc:
  case Format::jpeg:
    convert_from_intermediary_to_jpeg(output_buffer, len, &desc, argv[2]);
    break;
  case Format::nif:
  case Format::pm:
  case Format::png:
    convert_from_intermediary_to_png(output_buffer, len, &desc, argv[2]);
    break;
  case Format::ps:
  case Format::ras:
  case Format::tiff_motorola:
  case Format::tiff_intel:
  case Format::xcf:
  case Format::fig:
  case Format::xpm:
  case Format::qoi:
    convert_from_intermediary_to_qoi(output_buffer, len, &desc, argv[2]);
    break;
  case Format::tga:
    convert_from_intermediary_to_tga(output_buffer, len, &desc, argv[2]);
    break;
  default:
    fmt::print("unknown format to convert to\n");
  }
  std::free(output_buffer);
  return 0;
}
