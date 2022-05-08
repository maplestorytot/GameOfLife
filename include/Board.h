//
// Created by ryan on 05/05/22.
//

#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H
#include <utility>
#include <vector>
#include <memory>
namespace GameOfLife{
    enum CellState {DEAD, LIVE};
    using Row = int;
    using Column = int;
    struct Coordinate {
        Row row;
        Column col;
    };

    class IBoard {
    public:
        virtual ~IBoard() = default;
        virtual void doAdvance() = 0;
        virtual CellState operator[](const Coordinate & coordinate) const = 0;
    };

    enum BoardType {Matrix};
    class BoardFactory {
    public:
        static std::unique_ptr<IBoard> createBoard(BoardType boardType, std::initializer_list<
                std::initializer_list<CellState>> init_list);
    };

    class MatrixBoard : public IBoard {
    public:
        MatrixBoard(std::initializer_list<std::initializer_list<CellState>> init_list);
        void doAdvance() override;
        CellState operator[](const Coordinate & coordinate) const override;
    private:
        void advanceCell(const Coordinate& coordinate);
        int countLiveNeighbors(const Coordinate& coordinate);

    private:
        std::vector<std::vector<CellState>> board;
        std::vector<std::vector<CellState>> copy_board;
        size_t board_size;
    };
}  // namespace GameOfLife


#endif //GAMEOFLIFE_BOARD_H
