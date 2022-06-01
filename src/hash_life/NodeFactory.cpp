//
// Created by ryan on 25/05/22.
//

#include "../../include/hash_life/NodeFactory.h"
#include <gsl/gsl>
#include <math.h>

namespace GameOfLife {

    bool IsPowerOfTwoCopy(ulong x)
    {
        return (x != 0) && ((x & (x - 1)) == 0);
    }

    NodeFactory::NodeFactory(std::shared_ptr<NodeStorage> storage):node_storage(storage), empty_nodes({}){}

    Node * NodeFactory::getOrCreateNode(Node * nw, Node * ne,
                                            Node * sw, Node * se){
        Expects(nw != nullptr && ne != nullptr && sw != nullptr && se != nullptr);
        auto possible_node = node_storage->getNode({nw, ne, sw, se});
        if(possible_node.has_value()){
           return possible_node.value();
        }
        Expects(nw->get_level() == ne->get_level() &&
                nw->get_level() == sw->get_level() &&
                nw->get_level() == se->get_level()
        );
        return node_storage->storeNode({nw, ne, sw, se, nw->get_level() + 1});
    }

    Node * NodeFactory::createNode(const StartingBoardState& starting_state){
        NodeFactory::checkValidBoardSize(starting_state);
        unsigned board_size = starting_state.size();
        // size = 2^n, nlog2 = log(size)
        int level = log(starting_state.size())/log(2);

        return createNodeHelper(starting_state, board_size/2, board_size/2, level);
    }

    Node * NodeFactory::createNodeHelper(const StartingBoardState& starting_state,
                                         unsigned row, unsigned col, int level) {
        Expects(row > 0 && col > 0 && level > 0);
        if(level == STOP_LEVEL){
            return getOrCreateNode(
                    getLiveOrDeadNode(starting_state[row - 1][col - 1]),
                    getLiveOrDeadNode(starting_state[row - 1][col]),
                    getLiveOrDeadNode(starting_state[row][col - 1]),
                    getLiveOrDeadNode(starting_state[row][col])
                    );
        }

        unsigned level_length = 1 << (level - 2);
        return getOrCreateNode(
                createNodeHelper(starting_state, row - level_length, col - level_length,level - 1),
                createNodeHelper(starting_state, row - level_length, col + level_length,level - 1),
                createNodeHelper(starting_state, row + level_length, col - level_length,level - 1),
                createNodeHelper(starting_state, row + level_length, col + level_length, level - 1)
        );
    }

    Node * NodeFactory::getLiveOrDeadNode(CellState state){
        if(state == LIVE) {
            return node_storage->getLiveNode();
        }
        return node_storage->getDeadNode();
    }

    CellState NodeFactory::getLiveOrDeadNode(Node * node){
        Expects(node->get_level() == 0);
        if(node == node_storage->getLiveNode()) {
            return LIVE;
        } else if (node == node_storage->getDeadNode()) {
            return DEAD;
        }
        throw std::invalid_argument("Invalid Node Live or Dead!");
    }

    void NodeFactory::checkValidBoardSize(const StartingBoardState& starting_state){
        auto board_size = starting_state.size();
        Expects(IsPowerOfTwoCopy(board_size) && board_size >= MINIMUM_HASH_LIFE_BOARD_SIZE);
        for(const auto & row: starting_state){
            Expects(row.size() == board_size);
        }
    }

    Node * NodeFactory::getLiveNode(){
        return node_storage->getLiveNode();
    }

    Node * NodeFactory::getDeadNode(){
        return node_storage->getDeadNode();
    }

    Node * NodeFactory::getEmptyNodeAtLevel(int level){
        auto value = empty_nodes.find(level);
        if(value != empty_nodes.end()){
            return value->second;
        }
        auto empty_node = getEmptyNodeAtLevelHelper(level);
        empty_nodes[level] = empty_node;
        return empty_node;
    }

    Node * NodeFactory::getEmptyNodeAtLevelHelper(int level){
        if(level == 0){
            return getDeadNode();
        }
        return getOrCreateNode(getEmptyNodeAtLevelHelper(level - 1), getEmptyNodeAtLevelHelper(level - 1),
                               getEmptyNodeAtLevelHelper(level - 1), getEmptyNodeAtLevelHelper(level - 1));
    }
}  // namespace GameOfLife

