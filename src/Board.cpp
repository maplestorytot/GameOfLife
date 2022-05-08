//
// Created by ryan on 05/05/22.
//
#include "../include/Board.h"
#include <iostream>
#include <gsl/gsl>
#include <stdexcept>

namespace GameOfLife {
    CellState MatrixBoard::operator[](const Coordinate& coordinate) const {
        return board[coordinate.row][coordinate.col];
    }

    MatrixBoard::MatrixBoard(std::initializer_list<std::initializer_list<CellState>> input) : board_size(input.size()){
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

    void MatrixBoard::doAdvance() {
        for(int row = 0; row < board_size; row++){
            for(int col = 0; col < board_size; col++){
                advanceCell({row, col});
            }
        }
        board = copy_board;
    }

    void MatrixBoard::advanceCell(const Coordinate& coordinate){
        CellState& state = copy_board[coordinate.row][coordinate.col];
        auto liveNeighbors = countLiveNeighbors(coordinate);
        if((liveNeighbors == 0 || liveNeighbors == 1) && state == LIVE){
            state = DEAD;
        }else if(liveNeighbors == 2){
        }else if(liveNeighbors == 3 && state == DEAD){
            state = LIVE;
        }else if(liveNeighbors >= 4 && state == LIVE){
            state = DEAD;
        }
    }

    int MatrixBoard::countLiveNeighbors(const Coordinate& coordinate){
        unsigned count = 0;
        for(int row = coordinate.row - 1; row <= coordinate.row + 1; row++){
            int chosen_row = row;
            if(row < 0){
                chosen_row = board_size - 1;
            }else if(row >= board_size) {
                chosen_row = 0;
            }
            for(int col = coordinate.col - 1; col <= coordinate.col + 1; col++){
                int chosen_col = col;
                if(col < 0){
                    chosen_col = board_size - 1;
                }else if(col >= board_size) {
                    chosen_col = 0;
                }
                if(chosen_row == coordinate.row && chosen_col == coordinate.col){
                    continue;
                }
                if(board[chosen_row][chosen_col] == LIVE){
                    count++;
                }
            }
        }
        Ensures(count >= 0);
        return count;
    }

    std::unique_ptr<IBoard>
    BoardFactory::createBoard(BoardType boardType, std::initializer_list<std::initializer_list<CellState>> init_list) {
        if(boardType == BoardType::Matrix){
            return std::unique_ptr<IBoard>(new MatrixBoard(init_list));
        }
        throw std::invalid_argument( "Invalid Board Type!" );
    }
}  // namespace GameOfLife



