#include <benchmark/benchmark.h>

#include <array>
#include <checker/jig_checker.hpp>
#include <numeric>

static void BM_GenerateConnections(benchmark::State& state) {
  for (auto _ : state) {
    checker::generateConnections(state.range(0));
  }
}
BENCHMARK(BM_GenerateConnections)->Range(1, checker::NUM_CONNECTIONS);

static void BM_GeneratePieces(benchmark::State& state) {
  std::array<checker::Connection, checker::NUM_CONNECTIONS> connections{};
  std::iota(connections.begin(), connections.end(), 1);

  for (auto _ : state) {
    checker::generatePieces(connections);
  }
}
BENCHMARK(BM_GeneratePieces);

constexpr std::array<checker::Strategy, 3> strategies{
    checker::Strategy::linear,
    checker::Strategy::spiral,
    checker::Strategy::diagonal,
};

static void BM_UniqueCountSolutionsLinear(benchmark::State& state) {
  std::array<checker::Connection, checker::NUM_CONNECTIONS> connections{};
  std::iota(connections.begin(), connections.end(), 1);
  auto pieces = checker::generatePieces(connections);

  const auto strategy = strategies.at(state.range(0));
  for (auto _ : state) {
    checker::countSolutions(pieces, strategy);
  }
}
BENCHMARK(BM_UniqueCountSolutionsLinear)->DenseRange(0, strategies.size() - 1);

static void BM_TwoCountSolutionsLinear(benchmark::State& state) {
  constexpr checker::Connections ExampleConnections
      = {1,  1,  1,  -3, -6, 2, -5, 4, -6, -5, -2, -3, -4, -2, -3, -3, -7, -7, -6, -1,
         -1, -7, -7, 4,  -2, 5, -5, 3, -5, -2, 4,  -2, 5,  -3, -6, -4, 6,  -4, 1,  7};
  auto pieces = checker::generatePieces(ExampleConnections);

  const auto strategy = strategies.at(state.range(0));
  for (auto _ : state) {
    checker::countSolutions(pieces, strategy);
  }
}
BENCHMARK(BM_TwoCountSolutionsLinear)->DenseRange(0, strategies.size() - 1);
