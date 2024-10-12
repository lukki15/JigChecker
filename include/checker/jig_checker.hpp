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

  int64_t countSolutions(const Pieces& pieces);
  struct SolutionDirection {
    Connection right;
    Connection bottom;
  };
  using SolutionDirections = std::array<SolutionDirection, JIGSAW_SIZE * JIGSAW_SIZE>;
  int64_t countSolutions(size_t index, const Pieces& pieces, std::array<bool, JIGSAW_SIZE * JIGSAW_SIZE> &remaining, SolutionDirections& solution_directions);

}  // namespace checker
