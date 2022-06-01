//
// Created by ryan on 30/05/22.
//

#include "../../include/hash_life/NodePrinter.h"
#include <math.h>
#include <iostream>

namespace GameOfLife{
    NodePrinter::NodePrinter(std::shared_ptr<NodeFactory> node_factory):node_factory(node_factory) {}

    void NodePrinter::print(const Node* node) {
        StartingBoardState board;
        unsigned current_size = pow(2, node->get_level());
        board.resize(current_size);
        for(auto & row : board){
            row.resize(current_size);
        }
        printHelper(board, node, current_size / 2, current_size / 2);

        for(int row = 0; row < current_size; row++){
            for(int col = 0; col < current_size; col++){
                std::cout<<board[row][col]<<",";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }

    void NodePrinter::printHelper(StartingBoardState &board, const Node *node, unsigned int row, unsigned int col) {
        if(node->get_level() == 1){
            board[row - 1][col - 1] = node_factory->getLiveOrDeadNode(node->get_nw());
            board[row - 1][col] =    node_factory->getLiveOrDeadNode(node->get_ne());
            board[row][col - 1] =   node_factory->getLiveOrDeadNode(node->get_sw());
            board[row][col] =     node_factory->getLiveOrDeadNode(node->get_se());
//            board[row][col] = node_factory->getLiveOrDeadNode(current);
            return;
        }
        unsigned level_length = 1 << (node->get_level() - 2);
        printHelper(board, node->get_nw(), row - level_length, col - level_length);
        printHelper(board, node->get_ne(), row - level_length, col + level_length);
        printHelper(board, node->get_sw(), row + level_length, col - level_length);
        printHelper(board, node->get_se(), row + level_length, col + level_length);
    }
}


