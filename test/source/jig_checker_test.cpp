

#include <gtest/gtest.h>

#include <checker/jig_checker.hpp>
#include <cmath>

using UniqueConnections = testing::TestWithParam<size_t>;
INSTANTIATE_TEST_SUITE_P(JigCheckerParam, UniqueConnections,
                         testing::Range(1UL, checker::NUM_CONNECTIONS + 1));

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
