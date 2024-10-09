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
  std::array<int32_t, checker::NUM_CONNECTIONS> connections{};
  std::iota(connections.begin(), connections.end(), 1);

  for (auto _ : state) {
    checker::generatePieces(connections);
  }
}
BENCHMARK(BM_GeneratePieces);
