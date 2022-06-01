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
                                           StartingBoardState input);
        CellState& operator[](const Coordinate& coordinate) override;
        unsigned get_size() const override;
    private:
        unsigned board_size;
        std::vector<std::vector<CellState>> matrix;
    };

    class NestedVectorBoard : public IBoard {
        friend class BoardAlgorithmHelper;
    public:
        NestedVectorBoard(StartingBoardState init_list,  bool multi_threaded);
        void doAdvance() override;
        CellState operator[](const Coordinate& coordinate) override;
        void print() override;
    private:
        NestedVectorRepresentationOfMatrix board;
        NestedVectorRepresentationOfMatrix copy_board;
        bool multi_threaded;
    };
}  // namespace GameOfLife
#endif //GAMEOFLIFE_NESTEDVECTORMATRIX_H
