#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace checker {

  constexpr size_t JIGSAW_SIZE = 5;
  constexpr size_t NUM_CONNECTIONS = (JIGSAW_SIZE - 1) * JIGSAW_SIZE * 2;

  std::array<int32_t, NUM_CONNECTIONS> generateConnections(size_t unique_connections);

}  // namespace checker