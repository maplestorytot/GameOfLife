//
// Created by ryan on 19/05/22.
//

#ifndef GAMEOFLIFE_LIFEBOARD_H
#define GAMEOFLIFE_LIFEBOARD_H
#include "../Board.h"
#include <vector>
#include <boost/optional.hpp>

namespace GameOfLife {
    class SimpleLifeBoard : public IBoard {
    public:
        SimpleLifeBoard(StartingBoardState init_list);
        void doAdvance() override;
        CellState& operator[](const Coordinate& coordinate) override;
        void print() override;
    private:
        void setNextRow(int& ptr, int& abv_ptr);
        bool tryInitializePointers(int row);
        boost::optional<int> findFirstRowWithLiveCellStartingFromRow(int starting_row);
        int getRowAbove(int row);
        int getRowBelow(int row);
    private:
        std::vector<std::vector<Column>> live_list;
        std::vector<std::vector<Column>> copy_list;
        unsigned board_size;
        int above_row;
        int current_row;
        int below_row;
    };


}
#endif //GAMEOFLIFE_LIFEBOARD_H
