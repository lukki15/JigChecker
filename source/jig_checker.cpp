#include <stddef.h>                 // for size_t
#include <algorithm>                // for all_of, fill, shuffle
#include <array>                    // for array, array<>::value_type
#include <cassert>                  // for assert
#include <checker/jig_checker.hpp>  // for Direction, JIGSAW_SIZE, Pieces
#include <cstdint>                  // for int16_t, int32_t, uint64_t
#include <random>                   // for mt19937, uniform_int_distribution

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

  using SolutionDirections = Pieces;
  template <std::array<size_t, JIGSAW_SIZE * JIGSAW_SIZE> ORDER, size_t POS>
  static uint64_t countSolutionsOrder(const Pieces& pieces,
                                      std::array<bool, JIGSAW_SIZE * JIGSAW_SIZE>& remaining,
                                      SolutionDirections& solution_directions);

  constexpr std::array<size_t, JIGSAW_SIZE * JIGSAW_SIZE> linearOrder() {
    return {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
            13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
  }

  constexpr std::array<size_t, JIGSAW_SIZE * JIGSAW_SIZE> spiralOrder() {
    return {0,  1,  2, 3, 4, 9, 14, 19, 24, 23, 22, 21, 20,
            15, 10, 5, 6, 7, 8, 13, 18, 17, 16, 11, 12};
  }

  constexpr std::array<size_t, JIGSAW_SIZE * JIGSAW_SIZE> diagonalOrder() {
    return {0, 1, 5, 10, 6,  2,  3,  7,  11, 15, 20, 16, 12,
            8, 4, 9, 13, 17, 21, 22, 18, 14, 19, 23, 24};
  }

  uint64_t countSolutions(const Pieces& pieces, Strategy strategy) {
    std::array<bool, JIGSAW_SIZE * JIGSAW_SIZE> remaining;
    std::fill(remaining.begin(), remaining.end(), true);
    remaining.at(0) = false;

    SolutionDirections solution_directions{pieces.at(0)};

    switch (strategy) {
      case Strategy::linear:
        return countSolutionsOrder<linearOrder(), 1>(pieces, remaining, solution_directions);

      case Strategy::spiral:
        return countSolutionsOrder<spiralOrder(), 1>(pieces, remaining, solution_directions);

      case Strategy::diagonal:
        return countSolutionsOrder<diagonalOrder(), 1>(pieces, remaining, solution_directions);

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

  template <std::array<size_t, JIGSAW_SIZE * JIGSAW_SIZE> ORDER, size_t POS>
  static uint64_t countSolutionsOrder(const Pieces& pieces,
                                      std::array<bool, JIGSAW_SIZE * JIGSAW_SIZE>& remaining,
                                      SolutionDirections& solution_directions) {
    if constexpr (POS >= JIGSAW_SIZE * JIGSAW_SIZE) {
      assert(std::all_of(remaining.cbegin(), remaining.cend(), [](bool b) { return !b; }));
      return 1;
    } else {
      constexpr size_t index = ORDER.at(POS);

      constexpr auto x = index % JIGSAW_SIZE;
      constexpr auto y = index / JIGSAW_SIZE;

      constexpr bool rightBorder = x == (JIGSAW_SIZE - 1);
      constexpr bool leftBorder = x == 0;
      constexpr bool bottomBorder = y == (JIGSAW_SIZE - 1);
      constexpr bool topBorder = y == 0;

      int32_t top = topBorder ? 0 : -solution_directions.at((y - 1) * JIGSAW_SIZE + x).bottom;
      int32_t bottom = bottomBorder ? 0 : -solution_directions.at((y + 1) * JIGSAW_SIZE + x).top;
      int32_t left = leftBorder ? 0 : -solution_directions.at(index - 1).right;
      int32_t right = rightBorder ? 0 : -solution_directions.at(index + 1).left;

      constexpr auto match = [](bool border, int32_t dir, int32_t target) {
        return (!border && target == 0) || dir == target;
      };
      uint64_t solutions = 0;
      for (size_t i = 0; i < remaining.size(); i++) {
        if (!remaining.at(i)) {
          continue;
        }

        for (const auto& piece : getRotations(pieces.at(i))) {
          bool matchBottom = match(bottomBorder, piece.bottom, bottom);
          bool matchLeft = match(leftBorder, piece.left, left);
          bool matchRight = match(rightBorder, piece.right, right);
          bool matchTop = match(topBorder, piece.top, top);
          if (matchBottom && matchLeft && matchRight && matchTop) {
            solution_directions.at(index) = piece;
            remaining.at(i) = false;

            solutions
                += countSolutionsOrder<ORDER, POS + 1>(pieces, remaining, solution_directions);

            solution_directions.at(index) = {};
            remaining.at(i) = true;
          }
        }
      }

      return solutions;
    }
  }

}  // namespace checker
