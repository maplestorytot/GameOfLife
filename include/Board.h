//
// Created by ryan on 05/05/22.
//

#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H
#include <utility>
#include <vector>
#include <memory>
#include "util.h"

namespace GameOfLife{
        enum CellState {DEAD, LIVE};
        using Row = int;
        using Column = int;
        struct Coordinate {
            Row row;
            Column col;
        };

    class IBoard {
    DECLARE_CLASS_AS_INTERFACE(IBoard);
    public:
        virtual void doAdvance() = 0;
        virtual CellState& operator[](const Coordinate& coordinate) = 0;
        virtual void print() = 0;
    };

    enum BoardType {NestedVector, Vector};
    class BoardFactory {
    public:
        static std::unique_ptr<IBoard> createBoard(BoardType boardType, std::initializer_list<
                std::initializer_list<CellState>> init_list);
    };

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
}  // namespace GameOfLife


#endif //GAMEOFLIFE_BOARD_H
