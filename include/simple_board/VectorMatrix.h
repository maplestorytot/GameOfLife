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
                                     StartingBoardState input);
        CellState& operator[](const Coordinate& coordinate) override;
        unsigned get_size() const override;
    private:
        unsigned board_size;
        std::vector<CellState> matrix;
    };

    class VectorBoard : public IBoard {
        friend class BoardAlgorithmHelper;
    public:
        VectorBoard(StartingBoardState init_list, bool multi_threaded);
        void doAdvance() override;
        CellState operator[](const Coordinate& coordinate) override;
        void print() override;
    private:
        VectorRepresentationOfMatrix board;
        VectorRepresentationOfMatrix copy_board;
        bool multi_threaded;
    };
}
#endif //GAMEOFLIFE_VECTORMATRIX_H
