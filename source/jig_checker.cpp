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
    std::uniform_int_distribution<int16_t> dis_direction(0, 1);
    std::uniform_int_distribution<int16_t> dis_unique_connections(
        1, static_cast<int16_t>(unique_connections));

    for (size_t i = 1; i <= unique_connections; i++) {
      array.at(i - 1) = static_cast<checker::Connection>(i * (dis_direction(gen) * 2 - 1));
    }

    for (size_t i = unique_connections; i < array.size(); i++) {
      array.at(i) = static_cast<checker::Connection>(dis_unique_connections(gen)
                                                     * (dis_direction(gen) * 2 - 1));
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

  struct SolutionDirection {
    Connection right;
    Connection bottom;
  };
  using SolutionDirections = std::array<SolutionDirection, JIGSAW_SIZE * JIGSAW_SIZE>;
  static uint64_t countSolutionsLinear(size_t index, const Pieces& pieces,
                                       std::array<bool, JIGSAW_SIZE * JIGSAW_SIZE>& remaining,
                                       SolutionDirections& solution_directions);

  uint64_t countSolutions(const Pieces& pieces, Strategy strategy) {
    switch (strategy) {
      case Strategy::linear: {
        std::array<bool, JIGSAW_SIZE * JIGSAW_SIZE> remaining;
        std::fill(remaining.begin(), remaining.end(), true);
        remaining.at(0) = false;

        SolutionDirections solution_directions{};
        solution_directions.at(0) = {.right = pieces.at(0).right, .bottom = pieces.at(0).bottom};

        return countSolutionsLinear(1, pieces, remaining, solution_directions);
      }
      case Strategy::borderFirst:
        return 0;
      default:
        return 0;
    }
  }

  static std::array<checker::Direction, 4> getRotations(const checker::Direction& piece) {
    return {
        piece,
        {
            .right = piece.top,
            .bottom = piece.right,
            .left = piece.bottom,
            .top = piece.left,
        },
        {
            .right = piece.left,
            .bottom = piece.top,
            .left = piece.right,
            .top = piece.bottom,
        },
        {
            .right = piece.bottom,
            .bottom = piece.left,
            .left = piece.top,
            .top = piece.right,
        },
    };
  }

  static uint64_t countSolutionsLinear(size_t index, const Pieces& pieces,
                                       std::array<bool, JIGSAW_SIZE * JIGSAW_SIZE>& remaining,
                                       SolutionDirections& solution_directions) {
    if (index >= JIGSAW_SIZE * JIGSAW_SIZE) {
      assert(std::all_of(remaining.cbegin(), remaining.cend(), [](bool b) { return !b; }));
      return 1;
    }

    auto x = index % JIGSAW_SIZE;
    auto y = index / JIGSAW_SIZE;

    int32_t top = (y == 0) ? 0 : -solution_directions.at((y - 1) * JIGSAW_SIZE + x).bottom;
    int32_t left = -solution_directions.at(index - 1).right;
    bool rightBorder = x == (JIGSAW_SIZE - 1);
    bool bottomBorder = y == (JIGSAW_SIZE - 1);

    uint64_t solutions = 0;
    for (size_t i = 0; i < remaining.size(); i++) {
      if (!remaining.at(i)) {
        continue;
      }

      for (const auto& piece : getRotations(pieces.at(i))) {
        bool matchBottom = (piece.bottom == 0) == bottomBorder;
        bool matchLeft = piece.left == left;
        bool matchRight = (piece.right == 0) == rightBorder;
        bool matchTop = piece.top == top;
        if (matchBottom && matchLeft && matchRight && matchTop) {
          solution_directions.at(index) = {.right = piece.right, .bottom = piece.bottom};
          remaining.at(i) = false;

          solutions += countSolutionsLinear(index + 1, pieces, remaining, solution_directions);

          remaining.at(i) = true;
        }
      }
    }

    return solutions;
  }

}  // namespace checker
