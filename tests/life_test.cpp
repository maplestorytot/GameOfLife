//
// Created by ryan on 05/05/22.
//
#include <gtest/gtest.h>
#include "../include/Board.h"
#include "../include/BoardFactory.h"
#include "RandomBoardCreator.h"

namespace GameOfLife{
    TEST(LifeTest, IntegrationTestLongRunning){
        int BOARD_SIZE = 512;
        int NUM_GEN =  10;
        int64_t seed = RandomBoardCreator::DEFAULT_SEED;
//            int64_t seed = time(0);
        StartingBoardState STARTING_BOARD = RandomBoardCreator::CreateRandomBoard(BOARD_SIZE, seed);
        auto board = BoardFactory::createBoard(BoardType::NestedVector, STARTING_BOARD);
        auto board2 = BoardFactory::createBoard(BoardType::HashLife, STARTING_BOARD);

//        board->print();
//        board2->print();

        for(int i = 0; i < NUM_GEN; i++){
            board->doAdvance();
        }

        for(int i = 0; i < NUM_GEN; i++){
            board2->doAdvance();
        }

//        board->print();
//        board2->print();
        EXPECT_EQ(board->convert(), board2->convert());
    }

    class LifeTest :
            public testing::TestWithParam<BoardType> {
    };
    INSTANTIATE_TEST_SUITE_P(RuleTest, LifeTest, testing::ValuesIn(AllBoardTypes));

    TEST_P(LifeTest, OnlyAllowSquardBoards) {
        EXPECT_DEATH({
             auto board =
                     BoardFactory::createBoard(GetParam(), {{DEAD},{DEAD}});
        }, "");

        EXPECT_NO_FATAL_FAILURE({
             auto board =
                     BoardFactory::createBoard(GetParam(), {
                         {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                         {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                         {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                         {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                         {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                         {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                         {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                         {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD}});
         });
    }

    TEST_P(LifeTest, PopulatedCellWithOneNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        board->print();

        Coordinate cord = {2, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, PopulatedCellWithNoNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        board->print();
        Coordinate cord = {2, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, AtEdgePopulatedCellWithOneNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {LIVE,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,LIVE}
        });
        board->doAdvance();
        board->print();
        Coordinate cord = {7, 7};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, PopulatedCellWithFourOrMoreNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,LIVE,LIVE,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        Coordinate cord = {1, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, AtEdgePopulatedCellWithFourOrMoreNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,LIVE,LIVE},
                {LIVE,DEAD,DEAD,DEAD,DEAD,DEAD,LIVE,DEAD}
        });
        board->doAdvance();
        Coordinate cord = {7, 7};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, AtEdgePopulatedCellWithFourOrMoreNeighborsDies2) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {LIVE,DEAD,LIVE,LIVE,DEAD,LIVE,LIVE,DEAD},
                {LIVE,DEAD,DEAD,LIVE,DEAD,DEAD,LIVE,LIVE},
                {LIVE,LIVE,LIVE,LIVE,DEAD,LIVE,LIVE,LIVE},
                {LIVE,DEAD,DEAD,LIVE,LIVE,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,LIVE,LIVE,LIVE,LIVE,LIVE},
                {LIVE,LIVE,DEAD,DEAD,LIVE,DEAD,LIVE,LIVE},
                {LIVE,DEAD,LIVE,LIVE,LIVE,DEAD,DEAD,DEAD},
                {LIVE,DEAD,DEAD,DEAD,DEAD,LIVE,LIVE,DEAD}
        });
        board->doAdvance();
        Coordinate cord = {6, 0};
        EXPECT_EQ((*board)[cord], DEAD);
    }


    TEST_P(LifeTest, UnpopulatedCellWithThreeNeighborsLives) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,LIVE,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        board->print();
        Coordinate cord = {1, 2};
        EXPECT_EQ((*board)[cord], LIVE);
    }

    TEST_P(LifeTest, AtEdgeUnpopulatedCellWithThreeNeighborsLives) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        board->print();
        Coordinate cord = {0, 3};
        EXPECT_EQ((*board)[cord], LIVE);
    }

    TEST_P(LifeTest, PopulatedCellWithThreeNeighborsLives) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        board->print();
        Coordinate cord = {0, 3};
        EXPECT_EQ((*board)[cord], LIVE);
    }

    TEST_P(LifeTest, AtEdgePopulatedCellWithThreeNeighborsLives) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        board->print();
        Coordinate cord = {0, 3};
        EXPECT_EQ((*board)[cord], LIVE);
    }

    TEST_P(LifeTest, PopulatedCellWithTwoNeighborsLives) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        board->print();
        Coordinate cord = {0, 3};
        EXPECT_EQ((*board)[cord], LIVE);
    }

    TEST_P(LifeTest, AtEdgePopulatedCellWithTwoNeighborsLives) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,LIVE,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD,DEAD,DEAD,DEAD,DEAD}
        });
        board->doAdvance();
        board->print();
        Coordinate cord = {0, 3};
        EXPECT_EQ((*board)[cord], LIVE);
    }
}  // namespace GameOfLife
