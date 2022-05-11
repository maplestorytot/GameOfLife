//
// Created by ryan on 11/05/22.
//

#include "../include/simple_board/SimpleBoard.h"
#include "../include/simple_board/NestedVectorMatrix.h"
#include "../include/simple_board/VectorMatrix.h"
#include <gsl/gsl>
#include <iostream>

namespace GameOfLife {
    NestedVectorBoard::NestedVectorBoard(
            std::initializer_list<std::initializer_list<CellState>> input) : board(input.size(), input), copy_board(board){}

    VectorBoard::VectorBoard(
            std::initializer_list<std::initializer_list<CellState>> input) : board(input.size(), input), copy_board(board){}

    CellState &NestedVectorBoard::operator[](const Coordinate &coordinate) {
        return board[coordinate];
    }

    CellState &VectorBoard::operator[](const Coordinate &coordinate) {
        return board[coordinate];
    }

    CellState& NestedVectorRepresentationOfMatrix::operator[](const Coordinate& coordinate) {
        return matrix[coordinate.row][coordinate.col];
    }

    CellState& VectorRepresentationOfMatrix::operator[](const Coordinate &coordinate) {
        return matrix[coordinate.row * board_size + coordinate.col];
    }

    NestedVectorRepresentationOfMatrix::NestedVectorRepresentationOfMatrix(
            unsigned boardSize, std::initializer_list<std::initializer_list<CellState>> input)
            : board_size(boardSize) {
        Expects(input.size() == boardSize);
        Expects(board_size > 0);
        for(const auto & row : input){
            Expects(row.size() == boardSize);
            matrix.push_back({});
            for(const auto & cell : row){
                matrix[matrix.size() - 1].push_back(cell);
            }
        }
    }

    unsigned NestedVectorRepresentationOfMatrix::get_size() const {
        return board_size;
    }

    VectorRepresentationOfMatrix::VectorRepresentationOfMatrix(
            unsigned boardSize, std::initializer_list<std::initializer_list<CellState>> input)
            : board_size(boardSize){
        Expects(input.size() == boardSize);
        Expects(board_size > 0);
        for(const auto & row : input){
            Expects(row.size() == board_size);
            for(const auto & cell : row){
                matrix.push_back(cell);
            }
        }
    }

    unsigned VectorRepresentationOfMatrix::get_size() const {
        return board_size;
    }

    void NestedVectorBoard::doAdvance(){
        for(int row = 0; row < board.get_size(); row++){
            for(int col = 0; col < board.get_size(); col++){
                BoardAlgorithmHelper::advanceCell(board, copy_board, {row, col});
            }
        }
        board = copy_board; // MUST BE SEPARATE BECAUSE CANNOT VIRTUALIZE THIS ACTION WITH A BASE CLASS
    }

    void VectorBoard::doAdvance() {
        for(int row = 0; row < board.get_size(); row++){
            for(int col = 0; col < board.get_size(); col++){
                BoardAlgorithmHelper::advanceCell(board, copy_board, {row, col});
            }
        }
        board = copy_board; // MUST BE SEPARATE BECAUSE CANNOT VIRTUALIZE THIS ACTION WITH A BASE CLASS
    }

    void NestedVectorBoard::print() {
        BoardAlgorithmHelper::print(board);
    }

    void VectorBoard::print() {
        BoardAlgorithmHelper::print(board);
    }


    void BoardAlgorithmHelper::advanceCell(MatrixTemplate<CellState, Coordinate> &board,
                                           MatrixTemplate<CellState, Coordinate> &copy_board,
                                           const Coordinate &coordinate) {
        CellState& state = copy_board[coordinate];
        auto liveNeighbors = countLiveNeighbors(board, coordinate);
        if((liveNeighbors == 0 || liveNeighbors == 1) && state == LIVE){
            state = DEAD;
        }else if(liveNeighbors == 2){
        }else if(liveNeighbors == 3 && state == DEAD){
            state = LIVE;
        }else if(liveNeighbors >= 4 && state == LIVE){
            state = DEAD;
        }
    }

    int BoardAlgorithmHelper::countLiveNeighbors(MatrixTemplate<CellState, Coordinate> &board,
                                                 const Coordinate &coordinate) {
        int count = 0;
        for(int row = coordinate.row - 1; row <= coordinate.row + 1; row++){
            int chosen_row = row;
            if(row < 0){
                chosen_row = board.get_size() - 1;
            }else if(row >= board.get_size()) {
                chosen_row = 0;
            }
            for(int col = coordinate.col - 1; col <= coordinate.col + 1; col++){
                int chosen_col = col;
                if(col < 0){
                    chosen_col = board.get_size() - 1;
                }else if(col >= board.get_size()) {
                    chosen_col = 0;
                }
                if(chosen_row == coordinate.row && chosen_col == coordinate.col){
                    continue;
                }
                if(board[{chosen_row, chosen_col}] == LIVE){
                    count++;
                }
            }
        }
        Ensures(count >= 0);
        return count;
    }

    void BoardAlgorithmHelper::print(MatrixTemplate<CellState, Coordinate> &board) {
        for(int row = 0; row < board.get_size(); row++){
            for(int col = 0; col < board.get_size(); col++){
                std::cout<<board[{row, col}]<<",";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}  // namespace GameOfLife