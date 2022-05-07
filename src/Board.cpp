//
// Created by ryan on 05/05/22.
//
#include "../include/Board.h"
#include <iostream>
#include <gsl/gsl>

namespace GameOfLife {
    CellState Board::operator[](const Coordinate& coordinate) {
        return board[coordinate.row][coordinate.col];
    }

    Board::Board(std::initializer_list<std::initializer_list<CellState>> input) : board_size(input.size()){
        Expects(input.size() > 0);
        for(const auto & row : input){
            Expects(row.size() == input.size());
            board.push_back({});
            for(const auto & cell : row){
                board[board.size() - 1].push_back(cell);
            }
        }
        copy_board = board;
    }

    void Board::doAdvance() {
        for(int row = 0; row < board_size; row++){
            for(int col = 0; col < board_size; col++){
                advanceCell({row, col});
            }
        }
        board = copy_board;
    }

    void Board::advanceCell(const Coordinate& coordinate){
        std::unique_ptr<std::vector<CellState>> neighbors = obtainNeighbors(coordinate);
        CellState& state = copy_board[coordinate.row][coordinate.col];
        auto liveNeighbors = numberNeighborsAlive(*neighbors.get());
        if((liveNeighbors == 0 || liveNeighbors == 1) && state == LIVE){
            state = DEAD;
        }else if(liveNeighbors == 2){
        }else if(liveNeighbors == 3 && state == DEAD){
            state = LIVE;
        }else if(liveNeighbors >= 4 && state == LIVE){
            state = DEAD;
        }
    }

    std::unique_ptr<std::vector<CellState>> Board::obtainNeighbors(const Coordinate& coordinate){
        std::unique_ptr<std::vector<CellState>> neighbors = std::make_unique<std::vector<CellState>>();
        for(int row = coordinate.row - 1; row <= coordinate.row + 1; row++){
            int chosen_row = row;
            if(row < 0){
                chosen_row = board_size -1;
            }else if(row >= board_size) {
                chosen_row = 0;
            }
            for(int col = coordinate.col - 1; col <= coordinate.col + 1; col++){
                int chosen_col = col;
                if(col < 0){
                    chosen_col = board_size -1;
                }else if(col >= board_size) {
                    chosen_col = 0;
                }
                if(chosen_row == coordinate.row && chosen_col == coordinate.col){
                    continue;
                }
                neighbors->push_back(board[chosen_row][chosen_col]);
            }
        }
        return std::move(neighbors);
    }

    unsigned int Board::numberNeighborsAlive(const std::vector<CellState>& neighbors){
        unsigned int count = 0;
        for(const auto & cell: neighbors){
            if (cell == LIVE){
                count++;
            }
        }
        return count;
    }

}  // namespace GameOfLife



