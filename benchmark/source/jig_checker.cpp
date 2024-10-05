#include <benchmark/benchmark.h>
#include <checker/jig_checker.hpp>

static void BM_GenerateConnections(benchmark::State& state) {
  for (auto _ : state) {
    checker::generateConnections(state.range(0));
  }
}
BENCHMARK(BM_GenerateConnections)
    ->Arg(1)
    ->Arg(7)
    ->Arg(checker::NUM_CONNECTIONS/2)
    ->Arg(checker::NUM_CONNECTIONS);
