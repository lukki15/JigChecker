#include <algorithm>
#include <cassert>
#include <checker/jig_checker.hpp>
#include <random>

namespace checker {

  Connections generateConnections(size_t unique_connections) {
    assert(unique_connections > 0);
    assert(unique_connections <= NUM_CONNECTIONS);

    Connections array{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<checker::Connection> dis_direction(0, 1);
    std::uniform_int_distribution<checker::Connection> dis_unique_connections(
        1, static_cast<checker::Connection>(unique_connections));

    for (size_t i = 1; i <= unique_connections; i++) {
      array.at(i - 1) = static_cast<checker::Connection>(i) * (dis_direction(gen) * 2 - 1);
    }

    for (size_t i = unique_connections; i < array.size(); i++) {
      array.at(i) = dis_unique_connections(gen) * (dis_direction(gen) * 2 - 1);
    }

    std::shuffle(array.begin(), array.end(), gen);

    return array;
  }

  Pieces generatePieces(const Connections& connections) {
    Pieces pieces{};

    constexpr size_t x_pieces = (JIGSAW_SIZE - 1) * JIGSAW_SIZE;
    constexpr size_t y_pieces = (JIGSAW_SIZE - 1) * JIGSAW_SIZE;
    static_assert(x_pieces + y_pieces == NUM_CONNECTIONS);

    for (size_t i = 0; i < x_pieces; i++) {
      size_t x = i % (JIGSAW_SIZE - 1);
      size_t y = i / (JIGSAW_SIZE - 1);
      size_t pieces_i = y * JIGSAW_SIZE + x;
      pieces.at(pieces_i).right = connections.at(i);
      pieces.at(pieces_i + 1).left = -connections.at(i);
    }

    for (size_t i = 0; i < y_pieces; i++) {
      size_t x = i / (JIGSAW_SIZE - 1);
      size_t y = i % (JIGSAW_SIZE - 1);
      size_t pieces_i = y * JIGSAW_SIZE + x;
      pieces.at(pieces_i).bottom = connections.at(i + x_pieces);
      pieces.at(pieces_i + JIGSAW_SIZE).top = -connections.at(i + x_pieces);
    }

    return pieces;
  }

}  // namespace checker
