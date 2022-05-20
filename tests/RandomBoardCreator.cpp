//
// Created by ryan on 19/05/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "../include/Board.h"
#include "RandomBoardCreator.h"
namespace GameOfLife {
    StartingBoardState RandomBoardCreator::CreateRandomBoard(int board_size, int64_t seed) {
        boost::random::mt19937 gen;
        gen.seed(seed);
        boost::random::uniform_int_distribution<> dist(0, 1);

        StartingBoardState board;
        board.resize(board_size);
        for (int row = 0; row < board_size; row++) {
            board[row].resize(board_size);
            for (int col = 0; col < board_size; col++) {
                board[row][col] = static_cast<GameOfLife::CellState>(dist(gen));
            }
        }
        return board;
    }

    void BoardOutputter::Output(StartingBoardState board) {
        int board_size = board.size();
        printf("{\n");
        for (int row = 0; row < board_size; row++) {
            printf("{");
            for (int col = 0; col < board_size; col++) {
                if (board[row][col] == GameOfLife::LIVE) {
                    printf("LIVE");
                } else if (board[row][col] == GameOfLife::DEAD) {
                    printf("DEAD");
                }

                if (col < board_size - 1) {
                    printf(",");
                }
            }
            printf("}");
            if (row < board_size - 1) {
                printf(",\n");
            }
        }
        printf("\n};");
    }

}  // namespace GameOfLife
