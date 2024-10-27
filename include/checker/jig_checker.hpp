#pragma once

#include <array>    // for array
#include <cstddef>  // for size_t
#include <cstdint>  // for int8_t

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
    spiral,
    diagonal,
  };
  uint64_t countSolutions(const Pieces& pieces, Strategy strategy);
}  // namespace checker
