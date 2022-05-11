//
// Created by ryan on 11/05/22.
//

#ifndef GAMEOFLIFE_SIMPLEBOARD_H
#define GAMEOFLIFE_SIMPLEBOARD_H
#include "../Board.h"
#include <utility>
#include <vector>
#include <memory>
#include "../util.h"
namespace GameOfLife {
    template<class Value, class Index>
    class MatrixTemplate {
    DECLARE_CLASS_AS_INTERFACE(MatrixTemplate);
    public:
        virtual Value& operator[](const Index& index) = 0;
        virtual unsigned get_size() const = 0;
    };

    class BoardAlgorithmHelper {
    public:
        static void advanceCell(MatrixTemplate<CellState, Coordinate>& board,
                                MatrixTemplate<CellState, Coordinate>& copy_board,
                                const Coordinate& coordinate);
        static int countLiveNeighbors(MatrixTemplate<CellState, Coordinate>& board,
                                      const Coordinate& coordinate);
        static void print(MatrixTemplate<CellState, Coordinate>& board);
    };
}  // namespace GameOfLife
#endif //GAMEOFLIFE_SIMPLEBOARD_H
