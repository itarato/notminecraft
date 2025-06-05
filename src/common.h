#pragma once

#include <functional>

struct IntCoord {
  int x;
  int y;

  bool operator==(const IntCoord& other) const {
    return x == other.x && y == other.y;
  }
};

namespace std {
template <>
struct hash<IntCoord> {
  std::size_t operator()(const IntCoord& coord) const noexcept {
    std::size_t h1 = std::hash<int>{}(coord.x);
    std::size_t h2 = std::hash<int>{}(coord.y);
    return h1 ^ (h2 << 1);
  }
};
}  // namespace std
