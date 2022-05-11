//
// Created by ryan on 11/05/22.
//

#ifndef GAMEOFLIFE_VECTORMATRIX_H
#define GAMEOFLIFE_VECTORMATRIX_H
#include "SimpleBoard.h"
namespace GameOfLife {
    class VectorRepresentationOfMatrix : public MatrixTemplate<CellState, Coordinate> {
    public:
        VectorRepresentationOfMatrix(unsigned boardSize,
                                     std::initializer_list<std::initializer_list<CellState>> input);
        CellState& operator[](const Coordinate& coordinate) override;
        unsigned get_size() const override;
    private:
        unsigned board_size;
        std::vector<CellState> matrix;
    };

    class VectorBoard : public IBoard {
        friend class BoardAlgorithmHelper;
    public:
        VectorBoard(std::initializer_list<std::initializer_list<CellState>> init_list);
        void doAdvance() override;
        CellState& operator[](const Coordinate& coordinate) override;
        void print() override;
    private:
        VectorRepresentationOfMatrix board;
        VectorRepresentationOfMatrix copy_board;
    };
}
#endif //GAMEOFLIFE_VECTORMATRIX_H
