
#include <bits/std_abs.h>           // for abs
#include <gtest/gtest.h>            // for ParamIteratorInterface, Test, Mes...
#include <stdint.h>                 // for int32_t
#include <stdlib.h>                 // for size_t, abs
#include <array>                    // for array
#include <checker/jig_checker.hpp>  // for Strategy, generatePieces, Direction
#include <numeric>                  // for iota
#include <string>                   // for operator+, to_string, string

using UniqueConnections = testing::TestWithParam<size_t>;
INSTANTIATE_TEST_SUITE_P(JigCheckerParam, UniqueConnections,
                         testing::Range<size_t>(1UL, checker::NUM_CONNECTIONS + 1UL));

TEST_P(UniqueConnections, Check) {
  auto array = checker::generateConnections(GetParam());

  std::array<bool, checker::NUM_CONNECTIONS> unique_connections{};
  for (const auto& element : array) {
    unique_connections.at(std::abs(element) - 1) = true;
  }

  for (size_t i = 0; i < GetParam(); i++) {
    EXPECT_TRUE(unique_connections.at(i));
  }
  for (size_t i = GetParam(); i < checker::NUM_CONNECTIONS; i++) {
    EXPECT_FALSE(unique_connections.at(i));
  }
}

TEST(GeneratePieces, Empty) {
  auto pieces = checker::generatePieces({});

  for (const auto& piece : pieces) {
    EXPECT_EQ(piece.right, 0);
    EXPECT_EQ(piece.bottom, 0);
    EXPECT_EQ(piece.left, 0);
    EXPECT_EQ(piece.top, 0);
  }
}

void checkPiece(const checker::Pieces& pieces, size_t index, int32_t right, int32_t bottom,
                int32_t left, int32_t top) {
  SCOPED_TRACE("piece: " + std::to_string(index));
  const auto& piece = pieces.at(index);

  EXPECT_EQ(piece.right, right);
  EXPECT_EQ(piece.bottom, bottom);
  EXPECT_EQ(piece.left, left);
  EXPECT_EQ(piece.top, top);
}

constexpr checker::Connections ExampleConnections
    = {1,  1,  1,  -3, -6, 2, -5, 4, -6, -5, -2, -3, -4, -2, -3, -3, -7, -7, -6, -1,
       -1, -7, -7, 4,  -2, 5, -5, 3, -5, -2, 4,  -2, 5,  -3, -6, -4, 6,  -4, 1,  7};

TEST(GeneratePieces, Example) {
  auto pieces = checker::generatePieces(ExampleConnections);

  checkPiece(pieces, 0, 1, -1, 0, 0);
  checkPiece(pieces, 1, 1, -2, -1, 0);
  checkPiece(pieces, 2, 1, -5, -1, 0);
  checkPiece(pieces, 3, -3, 5, -1, 0);
  checkPiece(pieces, 4, 0, 6, 3, 0);

  checkPiece(pieces, 5, -6, -7, 0, 1);
  checkPiece(pieces, 6, 2, 5, 6, 2);
  checkPiece(pieces, 7, -5, -2, -2, 5);
  checkPiece(pieces, 8, 4, -3, 5, -5);
  checkPiece(pieces, 9, 0, -4, -4, -6);

  checkPiece(pieces, 10, -6, -7, 0, 7);
  checkPiece(pieces, 11, -5, -5, 6, -5);
  checkPiece(pieces, 12, -2, 4, 5, 2);
  checkPiece(pieces, 13, -3, -6, 2, 3);
  checkPiece(pieces, 14, 0, 1, 3, 4);

  checkPiece(pieces, 15, -4, 4, 0, 7);
  checkPiece(pieces, 16, -2, 3, 4, 5);
  checkPiece(pieces, 17, -3, -2, 2, -4);
  checkPiece(pieces, 18, -3, -4, 3, 6);
  checkPiece(pieces, 19, 0, 7, 3, -1);

  checkPiece(pieces, 20, -7, 0, 0, -4);
  checkPiece(pieces, 21, -7, 0, 7, -3);
  checkPiece(pieces, 22, -6, 0, 7, 2);
  checkPiece(pieces, 23, -1, 0, 6, 4);
  checkPiece(pieces, 24, 0, 0, 1, -7);
}

TEST(GeneratePieces, iota) {
  std::array<checker::Connection, checker::NUM_CONNECTIONS> connections{};
  std::iota(connections.begin(), connections.end(), 1);
  auto pieces = checker::generatePieces(connections);

  checkPiece(pieces, 0, 1, 21, 0, 0);
  checkPiece(pieces, 1, 2, 25, -1, 0);
  checkPiece(pieces, 2, 3, 29, -2, 0);
  checkPiece(pieces, 3, 4, 33, -3, 0);
  checkPiece(pieces, 4, 0, 37, -4, 0);

  checkPiece(pieces, 5, 5, 22, 0, -21);
  checkPiece(pieces, 6, 6, 26, -5, -25);
  checkPiece(pieces, 7, 7, 30, -6, -29);
  checkPiece(pieces, 8, 8, 34, -7, -33);
  checkPiece(pieces, 9, 0, 38, -8, -37);

  checkPiece(pieces, 10, 9, 23, 0, -22);
  checkPiece(pieces, 11, 10, 27, -9, -26);
  checkPiece(pieces, 12, 11, 31, -10, -30);
  checkPiece(pieces, 13, 12, 35, -11, -34);
  checkPiece(pieces, 14, 0, 39, -12, -38);

  checkPiece(pieces, 15, 13, 24, 0, -23);
  checkPiece(pieces, 16, 14, 28, -13, -27);
  checkPiece(pieces, 17, 15, 32, -14, -31);
  checkPiece(pieces, 18, 16, 36, -15, -35);
  checkPiece(pieces, 19, 0, 40, -16, -39);

  checkPiece(pieces, 20, 17, 0, 0, -24);
  checkPiece(pieces, 21, 18, 0, -17, -28);
  checkPiece(pieces, 22, 19, 0, -18, -32);
  checkPiece(pieces, 23, 20, 0, -19, -36);
  checkPiece(pieces, 24, 0, 0, -20, -40);
}

using SolutionStrategy = testing::TestWithParam<checker::Strategy>;
INSTANTIATE_TEST_SUITE_P(JigCheckerParam, SolutionStrategy,
                         testing::ValuesIn({
                             checker::Strategy::linear,
                             checker::Strategy::spiral,
                             checker::Strategy::diagonal,
                         }));

TEST_P(SolutionStrategy, UniqueSolution) {
  std::array<checker::Connection, checker::NUM_CONNECTIONS> connections{};
  std::iota(connections.begin(), connections.end(), 1);
  auto pieces = checker::generatePieces(connections);

  EXPECT_EQ(checker::countSolutions(pieces, GetParam()), 1);
}

TEST_P(SolutionStrategy, TwoSolutions) {
  auto pieces = checker::generatePieces(ExampleConnections);

  EXPECT_EQ(checker::countSolutions(pieces, GetParam()), 2);
}
