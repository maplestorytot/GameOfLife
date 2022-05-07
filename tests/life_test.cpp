//
// Created by ryan on 05/05/22.
//
#include <gtest/gtest.h>
#include "../include/Board.h"

// Board can be initialized with random input
namespace GameOfLife{
    TEST(RuleTest, OnlyAllowSquardBoards) {
        EXPECT_DEATH((Board{{DEAD},{DEAD}}), "");
        EXPECT_NO_FATAL_FAILURE((Board{{DEAD}}));
    }

    TEST(RuleTest, PopulatedCellWithOneNeighborsDies) {
        Board board = {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        };
        board.doAdvance();
        Coordinate cord = {2, 2};
        EXPECT_EQ(board[cord], DEAD);
    }

    TEST(RuleTest, PopulatedCellWithNoNeighborsDies) {
        Board board = {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        };
        board.doAdvance();
        Coordinate cord = {2, 2};
        EXPECT_EQ(board[cord], DEAD);
    }

    TEST(RuleTest, AtEdgePopulatedCellWithOneNeighborsDies) {
        Board board = {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,LIVE},
                {DEAD,DEAD,DEAD,LIVE},
        };
        board.doAdvance();
        Coordinate cord = {3, 3};
        EXPECT_EQ(board[cord], DEAD);
    }

    TEST(RuleTest, PopulatedCellWithFourOrMoreNeighborsDies) {
        Board board = {
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,LIVE,LIVE,LIVE},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        };
        board.doAdvance();
        Coordinate cord = {1, 2};
        EXPECT_EQ(board[cord], DEAD);
    }

    TEST(RuleTest, AtEdgePopulatedCellWithFourOrMoreNeighborsDies) {
        Board board = {
                {DEAD,DEAD,LIVE,DEAD},
                {LIVE,DEAD,LIVE,LIVE},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        };
        board.doAdvance();
        Coordinate cord = {1, 3};
        EXPECT_EQ(board[cord], DEAD);
    }

    TEST(RuleTest, UnpopulatedCellWithThreeNeighborsLives) {
        Board board = {
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,LIVE,DEAD,LIVE},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        };
        board.doAdvance();
        Coordinate cord = {1, 2};
        EXPECT_EQ(board[cord], LIVE);
    }

    TEST(RuleTest, AtEdgeUnpopulatedCellWithThreeNeighborsLives) {
        Board board = {
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,LIVE},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,LIVE},
        };
        board.doAdvance();
        Coordinate cord = {0, 3};
        EXPECT_EQ(board[cord], LIVE);
    }
}  // namespace GameOfLife
