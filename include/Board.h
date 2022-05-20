//
// Created by ryan on 05/05/22.
//

#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H
#include <utility>
#include <vector>
#include <memory>
#include "util.h"

namespace GameOfLife {
    enum CellState {DEAD, LIVE};
    using Row = int;
    using Column = int;
    struct Coordinate {
        Row row;
        Column col;
    };

    using StartingBoardState = std::vector<
            std::vector<CellState>>;

    class IBoard {
    DECLARE_CLASS_AS_INTERFACE(IBoard);
    public:
        virtual void doAdvance() = 0;
        virtual CellState& operator[](const Coordinate& coordinate) = 0;
        virtual void print() = 0;
    };

}  // namespace GameOfLife


#endif //GAMEOFLIFE_BOARD_H
