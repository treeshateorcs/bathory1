#pragma once

#include <array>
#include <span>
#include <cstdint>

using BYTE = unsigned char;

bool identify_format(std::span<std::uint8_t const> const &v,
                     std::span<std::uint8_t const> const &hint);
bool identify_bmp(const std::array<BYTE, 10> &v);
bool identify_fits(const std::array<BYTE, 10> &v);
bool identify_gif(const std::array<BYTE, 10> &v);
bool identify_gks(const std::array<BYTE, 10> &v);
bool identify_rgb(const std::array<BYTE, 10> &v);
bool identify_itc(const std::array<BYTE, 10> &v);
bool identify_jpeg(const std::array<BYTE, 10> &v);
bool identify_nif(const std::array<BYTE, 10> &v);
bool identify_pm(const std::array<BYTE, 10> &v);
bool identify_png(const std::array<BYTE, 10> &v);
bool identify_ps(const std::array<BYTE, 10> &v);
bool identify_ras(const std::array<BYTE, 10> &v);
bool identify_tiff_motorola(const std::array<BYTE, 10> &v);
bool identify_tiff_intel(const std::array<BYTE, 10> &v);
bool identify_xcf(const std::array<BYTE, 10> &v);
bool identify_fig(const std::array<BYTE, 10> &v);
bool identify_xpm(const std::array<BYTE, 10> &v);
