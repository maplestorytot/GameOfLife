//
// Created by ryan on 11/05/22.
//

#ifndef GAMEOFLIFE_BOARDFACTORY_H
#define GAMEOFLIFE_BOARDFACTORY_H
#include <memory>
#include "Board.h"
namespace GameOfLife {
    enum BoardType {NestedVector, Vector, MultiThreadedNestedVector, MultiThreadedVector};
    static BoardType AllBoardTypes [] = {NestedVector, Vector, MultiThreadedNestedVector, MultiThreadedVector};
    class BoardFactory {
    public:
        static std::unique_ptr<IBoard> createBoard(BoardType boardType, StartingBoardState init_list);
    };
}
#endif //GAMEOFLIFE_BOARDFACTORY_H
