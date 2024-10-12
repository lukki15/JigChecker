#include <benchmark/benchmark.h>

#include <checker/jig_checker.hpp>
#include <numeric>

static void BM_GenerateConnections(benchmark::State& state) {
  for (auto _ : state) {
    checker::generateConnections(state.range(0));
  }
}
BENCHMARK(BM_GenerateConnections)
    ->Arg(1)
    ->Arg(7)
    ->Arg(checker::NUM_CONNECTIONS / 2)
    ->Arg(checker::NUM_CONNECTIONS);

static void BM_GeneratePieces(benchmark::State& state) {
  std::array<checker::Connection, checker::NUM_CONNECTIONS> connections{};
  std::iota(connections.begin(), connections.end(), 1);

  for (auto _ : state) {
    checker::generatePieces(connections);
  }
}
BENCHMARK(BM_GeneratePieces);

static void BM_UniqueCountSolutions(benchmark::State& state) {
  std::array<checker::Connection, checker::NUM_CONNECTIONS> connections{};
  std::iota(connections.begin(), connections.end(), 1);
  auto pieces = checker::generatePieces(connections);

  for(auto _ : state){
    checker::countSolutions(pieces);
  }
}
BENCHMARK(BM_UniqueCountSolutions);

static void BM_TwoCountSolutions(benchmark::State& state) {
  constexpr checker::Connections ExampleConnections = {1,  1,  1,  -3, -6, 2,  -5, 4,  -6, -5, -2, -3, -4, -2,
                                         -3, -3, -7, -7, -6, -1, -1, -7, -7, 4,  -2, 5,  -5, 3,
                                         -5, -2, 4,  -2, 5,  -3, -6, -4, 6,  -4, 1,  7};
  auto pieces = checker::generatePieces(ExampleConnections);

  for(auto _ : state){
    checker::countSolutions(pieces);
  }
}
BENCHMARK(BM_TwoCountSolutions);
