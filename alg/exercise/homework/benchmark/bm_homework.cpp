#include <benchmark/benchmark.h>
#include "../homework.h"

static void BM_SinglyLinked_Insert(benchmark::State& state) {
  for (auto _ : state) {
    SinglyLinked l;
    for (int i = 0; i < state.range(0); ++i) {
      l.insert(i, "test");
    }
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_SinglyLinked_Insert)->Range(1, 1<<10);

static void BM_SinglyLinked_Remove(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    SinglyLinked l;
    for (int i = 0; i < state.range(0); ++i) {
      l.insert(i, "test");
    }
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      l.remove(0);
    }
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_SinglyLinked_Remove)->Range(1, 1<<10);

static void BM_DoublyLinked_Insert(benchmark::State& state) {
  for (auto _ : state) {
    DoublyLinked l;
    for (int i = 0; i < state.range(0); ++i) {
      l.insert(i, "test");
    }
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_DoublyLinked_Insert)->Range(1, 1<<10);

static void BM_DoublyLinked_Remove(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    DoublyLinked l;
    for (int i = 0; i < state.range(0); ++i) {
      l.insert(i, "test");
    }
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      l.remove(0);
    }
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_DoublyLinked_Remove)->Range(1, 1<<10);

static void BM_CircularBuffer_Push(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    CircularBuffer<char*> cb(state.range(0));
    char* test_string = "test";
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      cb.push(test_string);
    }
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_CircularBuffer_Push)->Range(1, 1<<10);

static void BM_CircularBuffer_Pop(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    CircularBuffer<char*> cb(state.range(0));
    char* test_string = "test";
    for (int i = 0; i < state.range(0); ++i) {
      cb.push(test_string);
    }
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      cb.pop();
    }
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_CircularBuffer_Pop)->Range(1, 1<<10);

