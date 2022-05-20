//
// Created by ryan on 11/05/22.
//
#include "../include/BoardFactory.h"
#include "../include/simple_board/NestedVectorMatrix.h"
#include "../include/simple_board/VectorMatrix.h"
#include <gsl/gsl>
#include <stdexcept>
namespace GameOfLife {
    std::unique_ptr<IBoard>
    BoardFactory::createBoard(BoardType boardType, StartingBoardState init_list) {
        if(boardType == BoardType::NestedVector){
            return std::unique_ptr<IBoard>(new NestedVectorBoard(init_list, false));
        } else if (boardType == BoardType::Vector){
            return std::unique_ptr<IBoard>(new VectorBoard(init_list, false));
        } else if (boardType == BoardType::MultiThreadedNestedVector){
            return std::unique_ptr<IBoard>(new NestedVectorBoard(init_list, true));
        } else if (boardType == BoardType::MultiThreadedVector){
            return std::unique_ptr<IBoard>(new VectorBoard(init_list, true));
        }

        throw std::invalid_argument( "Invalid Board Type!" );
    }
}  // namespace GameOfLife
