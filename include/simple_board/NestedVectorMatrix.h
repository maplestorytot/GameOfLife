//
// Created by ryan on 11/05/22.
//

#ifndef GAMEOFLIFE_NESTEDVECTORMATRIX_H
#define GAMEOFLIFE_NESTEDVECTORMATRIX_H
#include "SimpleBoard.h"
namespace GameOfLife {
    class NestedVectorRepresentationOfMatrix : public MatrixTemplate<CellState, Coordinate> {
    public:
        NestedVectorRepresentationOfMatrix(unsigned boardSize,
                                           std::initializer_list<std::initializer_list<CellState>> input);
        CellState& operator[](const Coordinate& coordinate) override;
        unsigned get_size() const override;
    private:
        unsigned board_size;
        std::vector<std::vector<CellState>> matrix;
    };

    class NestedVectorBoard : public IBoard {
        friend class BoardAlgorithmHelper;
    public:
        NestedVectorBoard(std::initializer_list<std::initializer_list<CellState>> init_list);
        void doAdvance() override;
        CellState& operator[](const Coordinate& coordinate) override;
        void print() override;
    private:
        NestedVectorRepresentationOfMatrix board;
        NestedVectorRepresentationOfMatrix copy_board;
    };
}  // namespace GameOfLife
#endif //GAMEOFLIFE_NESTEDVECTORMATRIX_H
