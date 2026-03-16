#include <benchmark/benchmark.h>

static void BM_old(benchmark::State& state) {

}

BENCHMARK(BM_old);


static void BM_new(benchmark::State& state) {
}

BENCHMARK(BM_new); // clazy:skip

BENCHMARK_MAIN();
