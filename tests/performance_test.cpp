//
// Created by ryan on 11/05/22.
//
#include <benchmark/benchmark.h>
#include "../include/Board.h"
#include "../include/BoardFactory.h"
#include "./RandomBoardCreator.h"
#include <ctime>
namespace GameOfLife {
    const int NUM_EPOCHS = 10;
    const std::vector<long> BOARD_SIZES = {10, 100, 1000};
    class LifePerformanceFixture : public benchmark::Fixture {
    public:
        void SetUp(const ::benchmark::State& state) {

            int64_t seed = RandomBoardCreator::DEFAULT_SEED;
//            int64_t seed = time(0);
            STARTING_BOARD = RandomBoardCreator::CreateRandomBoard(state.range(1), seed);
        }

        void TearDown(const ::benchmark::State& state) {
        }
        StartingBoardState& getStartingBoard(){return STARTING_BOARD;}
    private:
        StartingBoardState STARTING_BOARD;

    };

    BENCHMARK_DEFINE_F(LifePerformanceFixture, BM_GameOfLifeSpeed)(benchmark::State& state) {
        for (auto _ : state){
            auto board = BoardFactory::createBoard
                    (static_cast<BoardType>(state.range(0)), getStartingBoard());
//            board->print();
            for(int i = 0; i < NUM_EPOCHS; i++){
                board->doAdvance();
            }
        }
    }

    // Register the function as a benchmark
    BENCHMARK_REGISTER_F(LifePerformanceFixture, BM_GameOfLifeSpeed)->ArgsProduct(
            {{BoardType::NestedVector, BoardType::Vector, BoardType::MultiThreadedNestedVector,
              BoardType::MultiThreadedVector}, BOARD_SIZES});

    // Run the benchmark
    BENCHMARK_MAIN();
}  // namespace GameOfLife

