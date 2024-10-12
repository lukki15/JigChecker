#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace checker {

  constexpr size_t JIGSAW_SIZE = 5;
  constexpr size_t NUM_CONNECTIONS = (JIGSAW_SIZE - 1) * JIGSAW_SIZE * 2;

  using Connection = int8_t;
  using Connections = std::array<Connection, NUM_CONNECTIONS>;
  Connections generateConnections(size_t unique_connections);

  struct Direction {
    Connection right;
    Connection bottom;
    Connection left;
    Connection top;
  };
  using Pieces = std::array<Direction, JIGSAW_SIZE * JIGSAW_SIZE>;
  Pieces generatePieces(const Connections& connections);

  enum class Strategy {
    linear,
    borderFirst,
  };
  uint64_t countSolutions(const Pieces& pieces, Strategy strategy);
}  // namespace checker
