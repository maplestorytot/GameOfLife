//
// Created by ryan on 19/05/22.
//

#ifndef GAMEOFLIFE_RANDOMBOARDCREATOR_H
#define GAMEOFLIFE_RANDOMBOARDCREATOR_H
#include "../include/Board.h"
#include <boost/random/mersenne_twister.hpp>

namespace GameOfLife {
    class RandomBoardCreator {
    public:
        static const int DEFAULT_SEED = boost::mt19937_64::default_seed;
        static StartingBoardState CreateRandomBoard(int board_size, int64_t seed = DEFAULT_SEED);
    };

    class BoardOutputter {
    public:
        static void Output(StartingBoardState board);
    };
}  // namespace GameOfLife
#endif //GAMEOFLIFE_RANDOMBOARDCREATOR_H
