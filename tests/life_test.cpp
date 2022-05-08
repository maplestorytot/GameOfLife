//
// Created by ryan on 05/05/22.
//
#include <gtest/gtest.h>
#include "../include/Board.h"

// SimpleBoard can be initialized with random input
namespace GameOfLife{
    class TestConfig {
    public:
        static const BoardType BOARD_TYPE = BoardType::Simple;
    };

    TEST(RuleTest, OnlyAllowSquardBoards) {
        EXPECT_DEATH({
             auto board =
                     BoardFactory::createBoard(TestConfig::BOARD_TYPE, {{DEAD},{DEAD}});
        }, "");

        EXPECT_NO_FATAL_FAILURE({
             auto board =
                     BoardFactory::createBoard(TestConfig::BOARD_TYPE, {{DEAD}});
         });
    }

    TEST(RuleTest, PopulatedCellWithOneNeighborsDies) {
        auto board = BoardFactory::createBoard(TestConfig::BOARD_TYPE, {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {2, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST(RuleTest, PopulatedCellWithNoNeighborsDies) {
        auto board = BoardFactory::createBoard(TestConfig::BOARD_TYPE, {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {2, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST(RuleTest, AtEdgePopulatedCellWithOneNeighborsDies) {
        auto board = BoardFactory::createBoard(TestConfig::BOARD_TYPE, {
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,LIVE},
                {DEAD,DEAD,DEAD,LIVE},
        });
        board->doAdvance();
        Coordinate cord = {3, 3};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST(RuleTest, PopulatedCellWithFourOrMoreNeighborsDies) {
        auto board = BoardFactory::createBoard(TestConfig::BOARD_TYPE, {
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,LIVE,LIVE,LIVE},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {1, 2};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST(RuleTest, AtEdgePopulatedCellWithFourOrMoreNeighborsDies) {
        auto board = BoardFactory::createBoard(TestConfig::BOARD_TYPE, {
                {DEAD,DEAD,LIVE,DEAD},
                {LIVE,DEAD,LIVE,LIVE},
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {1, 3};
        EXPECT_EQ((*board)[cord], DEAD);
    }

    TEST(RuleTest, UnpopulatedCellWithThreeNeighborsLives) {
        auto board = BoardFactory::createBoard(TestConfig::BOARD_TYPE, {
                {DEAD,DEAD,LIVE,DEAD},
                {DEAD,LIVE,DEAD,LIVE},
                {DEAD,DEAD,DEAD,DEAD},
                {DEAD,DEAD,DEAD,DEAD},
        });
        board->doAdvance();
        Coordinate cord = {1, 2};
        EXPECT_EQ((*board)[cord], LIVE);
    }

    TEST(RuleTest, AtEdgeUnpopulatedCellWithThreeNeighborsLives) {
        auto board = BoardFactory::createBoard(TestConfig::BOARD_TYPE, {
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
