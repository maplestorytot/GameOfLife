//
// Created by ryan on 21/05/22.
//
#include "../include/life_board/LifeBoardSimple.h"
#include <gsl/gsl>

namespace GameOfLife {
//    class LifeBoardLookUpTable {
//    public:
//        using Index = char;
//        CellState lookup(Index index){return lookup_table[index];}
//    private:
//        std::array<CellState, 512> lookup_table;
//    };
//
//    CellState LifeBoardLookUpTable::lookup(Index index) {
//
//    }


    SimpleLifeBoard::SimpleLifeBoard(StartingBoardState init_list):board_size(init_list.size()){
        Expects(board_size > 0);
        live_list.resize(board_size);
        for(int row = 0; row < board_size; row++){
            Expects(init_list[row].size() == board_size);
            for(int col = 0; col < board_size; col++){
                if(init_list[row][col] == LIVE){
                    live_list[row].push_back(col);
                }
            }
        }
        copy_list = live_list;
    }
    void SimpleLifeBoard::doAdvance(){
        current_row = 0;
        while(tryInitializePointers(current_row)){
            advanceRow();
        }
    }

    void SimpleLifeBoard::advanceRow(){
        for(const auto & col : live_list[current_row]){
            advanceCellAndItsNeighbors({current_row, col});
        }
    }

    void SimpleLifeBoard::advanceCellAndItsNeighbors(Coordinate coordinate){
        for(int row = coordinate.row - 1; row <= coordinate.row + 1; row++){
            for(int col = coordinate.col - 1; col <= coordinate.col + 1; col++){
                advanceCell({row, col});
            }
        }
    }

    void SimpleLifeBoard::

    bool SimpleLifeBoard::tryInitializePointers(int row){
        auto result = findFirstRowWithLiveCellStartingFromRow(row);
        if (result.has_value()) {
            current_row = result.value();
            above_row = getRowAbove(current_row);
            below_row = getRowBelow(current_row);
        }
    }

    int SimpleLifeBoard::getRowAbove(int row){
        if(row == 0){
            return board_size - 1;
        }
        return row - 1;
    }

    int SimpleLifeBoard::getRowBelow(int row){
        if(row == board_size - 1){
            return 0;
        }
        return row + 1;
    }

    int SimpleLifeBoard::getColLeft(int col){

    }

    int SimpleLifeBoard::getColRight(int col){}

    boost::optional<int> SimpleLifeBoard::findFirstRowWithLiveCellStartingFromRow(int starting_row){
        Expects(0 <= starting_row && starting_row < board_size);
        int ptr = starting_row;
        while(live_list[ptr].size() == 0){
            ptr++;
        }
        return ptr;
    }

//
//
//    void SimpleLifeBoard::setNextRow(int& ptr, int& abv_ptr){
//        ptr = abv_ptr;
//        while(live_list[ptr].row == live_list[abv_ptr].row){
//            ptr++;
//        }
//    }

    CellState& SimpleLifeBoard::operator[](const Coordinate& coordinate){}
    void SimpleLifeBoard::print(){}

}
