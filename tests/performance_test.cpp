//
// Created by ryan on 11/05/22.
//
#include <benchmark/benchmark.h>
#include "../include/Board.h"
#include "../include/BoardFactory.h"
namespace GameOfLife {
    const int NUM_EPOCHS = 10000;
    static void BM_GameOfLifeSpeed(benchmark::State& state) {
        for (auto _ : state){
            auto board = BoardFactory::createBoard(BoardType::Vector, {
                    {DEAD,DEAD,DEAD,DEAD},
                    {DEAD,DEAD,LIVE,DEAD},
                    {DEAD,DEAD,LIVE,DEAD},
                    {DEAD,DEAD,DEAD,DEAD},
            });
            for(int i = 0; i < NUM_EPOCHS; i++){
                board->doAdvance();
            }
        }
    }

    // Register the function as a benchmark
    BENCHMARK(BM_GameOfLifeSpeed)->Arg(BoardType::Vector)->Arg(BoardType::NestedVector);

    // Run the benchmark
    BENCHMARK_MAIN();
}  // namespace GameOfLife

