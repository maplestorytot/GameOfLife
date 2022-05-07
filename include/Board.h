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

    class Board {
    public:
        Board(std::initializer_list<std::initializer_list<CellState>> init_list);
        void doAdvance();
        CellState operator[](const Coordinate & coordinate);
    private:
        void advanceCell(const Coordinate& coordinate);
        std::unique_ptr<std::vector<CellState>> obtainNeighbors(const Coordinate& coordinate);
        unsigned int numberNeighborsAlive(const std::vector<CellState>& neighbors);


    private:
        std::vector<std::vector<CellState>> board;
        std::vector<std::vector<CellState>> copy_board;
        size_t board_size;
    };
}


#endif //GAMEOFLIFE_BOARD_H
