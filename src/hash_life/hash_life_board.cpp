//
// Created by ryan on 24/05/22.
//

#include "../../include/hash_life/hash_life_board.h"
#include <memory>
#include <gsl/gsl>
#include <math.h>

namespace GameOfLife {
    bool IsPowerOfTwo(ulong x)
    {
        return (x != 0) && ((x & (x - 1)) == 0);
    }

    HashLifeBoard::HashLifeBoard(StartingBoardState init_list, std::shared_ptr<NodeStorage> storage)
    : node_factory(std::make_shared<NodeFactory>(storage)), transformer(node_factory), printer(node_factory),
    board_size(init_list.size()*2), root(nullptr) {
        Expects(IsPowerOfTwo(board_size));
        auto core = node_factory->createNode(init_list);
        empty_fourth = node_factory->getEmptyNodeAtLevel(core->get_level() - 1);
//        printer.print(core);
        root = createBorderAround(core->get_nw(), core->get_ne(), core->get_sw(), core->get_se());
    }

    void HashLifeBoard::doAdvance() {

        copyBorders();
//        printer.print(root);
        auto new_core = transformer.nextGeneration(root);
        root = createBorderAround(new_core->get_nw(), new_core->get_ne(), new_core->get_sw(), new_core->get_se());
        Expects(pow(2, root->get_level()) == board_size);
    }

    void HashLifeBoard::copyBorders(){
        auto core = node_factory->getOrCreateNode(root->get_nw()->get_se(), root->get_ne()->get_sw(),
                                             root->get_sw()->get_ne(), root->get_se()->get_nw());

        auto nw_mirror = transformer.createMirror(Node::NW, core->get_nw());
        auto ne_mirror = transformer.createMirror(Node::NE, core->get_ne());
        auto sw_mirror = transformer.createMirror(Node::SW, core->get_sw());
        auto se_mirror = transformer.createMirror(Node::SE, core->get_se());

        // TODO Check!
        root = node_factory->getOrCreateNode(
                node_factory->getOrCreateNode(se_mirror.corner, sw_mirror.outleft, ne_mirror.outright, core->get_nw()),
                node_factory->getOrCreateNode(se_mirror.outright, sw_mirror.corner, core->get_ne(), nw_mirror.outleft),
                node_factory->getOrCreateNode(se_mirror.outleft, core->get_sw(), ne_mirror.corner, nw_mirror.outright),
                node_factory->getOrCreateNode(core->get_se(), sw_mirror.outright, ne_mirror.outleft, nw_mirror.corner)
                );
    }

    Node* HashLifeBoard::createBorderAround(Node * nw, Node * ne, Node * sw,
                                        Node * se){
        // TODO: Check!
        auto root_nw = node_factory->
                getOrCreateNode(empty_fourth, empty_fourth, empty_fourth, nw);
        auto root_ne = node_factory->
                getOrCreateNode(empty_fourth, empty_fourth, ne, empty_fourth);
        auto root_sw = node_factory->
                getOrCreateNode(empty_fourth, sw, empty_fourth, empty_fourth);
        auto root_se = node_factory->
                getOrCreateNode(se, empty_fourth , empty_fourth, empty_fourth);

        return node_factory->getOrCreateNode(root_nw, root_ne, root_sw, root_se);
    }

    CellState HashLifeBoard::operator[](const Coordinate &coordinate) {
        auto core = node_factory->getOrCreateNode(
                root->get_nw()->get_se(),
                root->get_ne()->get_sw(),
                root->get_sw()->get_ne(),
                root->get_se()->get_nw());
        StartingBoardState board;
        unsigned current_size = pow(2, core->get_level());
        board.resize(current_size);
        for(auto & row : board){
            row.resize(current_size);
        }
        printer.printHelper(board, core, current_size / 2, current_size / 2);
        return board[coordinate.row][coordinate.col];
//        unsigned row = board_size / 4;
//        unsigned col = board_size / 4;
//
//        auto current = node_factory->getOrCreateNode(
//                root->get_nw()->get_se(),
//                root->get_ne()->get_sw(),
//                root->get_sw()->get_ne(),
//                root->get_se()->get_nw());
//        int level_length = 1 << (current->get_level() - 2);
//        while(true) {
//            if (row >= coordinate.row && col >= coordinate.col){
//                current = current->get_nw();
//                row = row - level_length;
//                col = col - level_length;
//            } else if (row >= coordinate.row && col < coordinate.col){
//                current = current->get_ne();
//                row = row - level_length;
//                col = col + level_length;
//            } else if (row < coordinate.row && col >= coordinate.col){
//                current = current->get_sw();
//                row = row + level_length;
//                col = col - level_length;
//            } else if (row < coordinate.row && col <= coordinate.col){
//                current = current->get_se();
//                row = row + level_length;
//                col = col + level_length;
//            } else {
//                /*if(current->get_level() != 0){
//                    current = current->get_se();
//                }
//                while(current->get_level() != 0){
//                    current = current->get_nw();
//                }*/
//                return node_factory->getLiveOrDeadNode(current);
//            }
//
//            level_length = level_length >> 1;
//            if(level_length < 0){
//                level_length = 1;
//            }
//        }
//        Expects(false);
    }


    void HashLifeBoard::print() {
        printer.print(node_factory->getOrCreateNode(
                root->get_nw()->get_se(),
                root->get_ne()->get_sw(),
                root->get_sw()->get_ne(),
                root->get_se()->get_nw()));
    }

    StartingBoardState HashLifeBoard::convert() {
        auto core = node_factory->getOrCreateNode(
                root->get_nw()->get_se(),
                root->get_ne()->get_sw(),
                root->get_sw()->get_ne(),
                root->get_se()->get_nw());
        StartingBoardState board;
        unsigned current_size = pow(2, core->get_level());
        board.resize(current_size);
        for(auto & row : board){
            row.resize(current_size);
        }
        printer.printHelper(board, core, current_size / 2, current_size / 2);
        return board;
    }


}  // namespace GameOfLife