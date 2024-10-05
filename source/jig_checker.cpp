#include <algorithm>
#include <cassert>
#include <checker/jig_checker.hpp>
#include <random>

namespace checker {

  std::array<int32_t, NUM_CONNECTIONS> generateConnections(size_t unique_connections) {
    assert(unique_connections > 0);
    assert(unique_connections <= NUM_CONNECTIONS);

    std::array<int32_t, NUM_CONNECTIONS> array{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> dis_direction(0, 1);
    std::uniform_int_distribution<int32_t> dis_unique_connections(1, unique_connections);

    for (size_t i = 1; i <= unique_connections; i++) {
      array.at(i - 1) = i * (dis_direction(gen) * 2 - 1);
    }

    for (size_t i = unique_connections; i < array.size(); i++) {
      array.at(i) = dis_unique_connections(gen) * (dis_direction(gen) * 2 - 1);
    }

    std::shuffle(array.begin(), array.end(), gen);

    return array;
  }

}  // namespace checker
