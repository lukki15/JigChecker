#include <benchmark/benchmark.h>
#include <greeter/greeter.h>
#include <greeter/version.h>

static void BM_Greet(benchmark::State& state) {
  using namespace greeter;
  Greeter greeter("Tests");

  for (auto _ : state) greeter.greet(static_cast<LanguageCode>(state.range(0)));
}
BENCHMARK(BM_Greet)
    ->Arg(static_cast<int>(greeter::LanguageCode::EN))
    ->Arg(static_cast<int>(greeter::LanguageCode::DE))
    ->Arg(static_cast<int>(greeter::LanguageCode::ES))
    ->Arg(static_cast<int>(greeter::LanguageCode::FR));
