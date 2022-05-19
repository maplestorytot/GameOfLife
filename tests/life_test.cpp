//
// Created by ryan on 05/05/22.
//
#include <gtest/gtest.h>
#include "../include/Board.h"
#include "../include/BoardFactory.h"

namespace GameOfLife{
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
                     BoardFactory::createBoard(GetParam(), {{DEAD}});
         });
    }

    TEST_P(LifeTest, PopulatedCellWithOneNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {2, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, PopulatedCellWithNoNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {2, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, AtEdgePopulatedCellWithOneNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,LIVE},
                {DEAD,DEAD,DEAD,LIVE},
        });
        board->doAdvance();
        Coordinate cord = {3, 3};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, PopulatedCellWithFourOrMoreNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,LIVE,LIVE,LIVE},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {1, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, AtEdgePopulatedCellWithFourOrMoreNeighborsDies) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,DEAD},
                {LIVE,DEAD,LIVE,LIVE},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {1, 3};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST_P(LifeTest, UnpopulatedCellWithThreeNeighborsLives) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,LIVE,DEAD,LIVE},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {1, 2};
        EXPECT_EQ((*board)[cord], LIVE);
    }

    TEST_P(LifeTest, AtEdgeUnpopulatedCellWithThreeNeighborsLives) {
        auto board = BoardFactory::createBoard(GetParam(), {
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,LIVE},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,LIVE},
        });
        board->doAdvance();
        Coordinate cord = {0, 3};
        EXPECT_EQ((*board)[cord], LIVE);
    }
}  // namespace GameOfLife
