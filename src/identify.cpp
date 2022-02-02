#include "identify.hpp"
#include <algorithm>

bool identify_format(std::span<std::uint8_t const> const &v,
                     std::span<std::uint8_t const> const &hint) {
  auto it = std::search(v.begin(), v.end(), hint.begin(), hint.end());
  return it == v.begin();
}
