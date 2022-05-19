//
// Created by ryan on 11/05/22.
//

#ifndef GAMEOFLIFE_BOARDFACTORY_H
#define GAMEOFLIFE_BOARDFACTORY_H
#include <memory>
#include "Board.h"
namespace GameOfLife {
    enum BoardType {NestedVector, Vector};
    static BoardType AllBoardTypes [] = {NestedVector, Vector};
    class BoardFactory {
    public:
        static std::unique_ptr<IBoard> createBoard(BoardType boardType, std::initializer_list<
        std::initializer_list<CellState>> init_list);
    };
}
#endif //GAMEOFLIFE_BOARDFACTORY_H
