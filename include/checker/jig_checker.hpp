#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace checker {

  constexpr size_t JIGSAW_SIZE = 5;
  constexpr size_t NUM_CONNECTIONS = (JIGSAW_SIZE - 1) * JIGSAW_SIZE * 2;

  enum Direction {
    right,
    bottom,
    left,
    top,
  };

  using Connections = std::array<int32_t, NUM_CONNECTIONS>;
  Connections generateConnections(size_t unique_connections);

  using Pieces = std::array<std::array<int32_t, 4>, JIGSAW_SIZE * JIGSAW_SIZE>;
  Pieces generatePieces(const Connections& connections);

}  // namespace checker