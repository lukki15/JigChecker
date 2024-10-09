

#include <gtest/gtest.h>

#include <checker/jig_checker.hpp>
#include <cmath>

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
    EXPECT_EQ(piece.at(checker::Direction::right), 0);
    EXPECT_EQ(piece.at(checker::Direction::bottom), 0);
    EXPECT_EQ(piece.at(checker::Direction::left), 0);
    EXPECT_EQ(piece.at(checker::Direction::top), 0);
  }
}

void checkPiece(const checker::Pieces& pieces, size_t index, int32_t right, int32_t bottom,
                int32_t left, int32_t top) {
  SCOPED_TRACE("piece: " + std::to_string(index));
  const auto& piece = pieces.at(index);

  EXPECT_EQ(piece.at(checker::Direction::right), right);
  EXPECT_EQ(piece.at(checker::Direction::bottom), bottom);
  EXPECT_EQ(piece.at(checker::Direction::left), left);
  EXPECT_EQ(piece.at(checker::Direction::top), top);
}

TEST(GeneratePieces, Example) {
  auto pieces = checker::generatePieces({1,  1,  1,  -3, -6, 2,  -5, 4,  -6, -5, -2, -3, -4, -2,
                                         -3, -3, -7, -7, -6, -1, -1, -7, -7, 4,  -2, 5,  -5, 3,
                                         -5, -2, 4,  -2, 5,  -3, -6, -4, 6,  -4, 1,  7});

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
