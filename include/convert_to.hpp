#pragma once

#include "identify.hpp"
#include "qoi.h"
#include <cstdlib>
#include <string>

void convert_from_intermediary_to_bmp(BYTE *output_buffer, std::size_t *len,
                                      qoi_desc *desc,
                                      const std::string &output_filename);
void convert_from_intermediary_to_tga(BYTE *output_buffer, std::size_t *len,
                                      qoi_desc *desc,
                                      const std::string &output_filename);
void convert_from_intermediary_to_jpeg(BYTE *output_buffer, std::size_t *len,
                                       qoi_desc *desc,
                                       const std::string &output_filename);
void convert_from_intermediary_to_png(BYTE *output_buffer, std::size_t *len,
                                      qoi_desc *desc,
                                      const std::string &output_filename);
void convert_from_intermediary_to_qoi(BYTE *output_buffer, std::size_t *len,
                                      qoi_desc *desc,
                                      const std::string &output_filename);
