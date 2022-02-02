#pragma once

#include "format.hpp"
#include "identify.hpp"
#include "qoi.h"
#include <string>
#include <vector>

void determine_output_format(std::string &output_extension,
                             Format &output_format);
void convert_qoi_to_intermediary(const std::vector<BYTE> &i, BYTE **o,
                                 std::size_t *len, qoi_desc *desc);
void convert_to_intermediary(const std::vector<BYTE> &i, BYTE **o,
                             std::size_t *len, qoi_desc *desc);
