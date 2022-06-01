//
// Created by ryan on 25/05/22.
//

#ifndef GAMEOFLIFE_NODEFACTORY_H
#define GAMEOFLIFE_NODEFACTORY_H
#include "Node.h"
#include "NodeStorage.h"
#include "../Board.h"

#define MINIMUM_HASH_LIFE_BOARD_SIZE 8
namespace GameOfLife {
    static const unsigned STOP_LEVEL = 1;
    class NodeFactory {
    public:
        NodeFactory(std::shared_ptr<NodeStorage> storage);
        Node * getOrCreateNode(Node * nw, Node * ne,
                                                Node * sw, Node * se);
        Node * createNode(const StartingBoardState& starting_state);
        Node * getEmptyNodeAtLevel(int level);
        CellState getLiveOrDeadNode(Node * node);
        Node * getLiveOrDeadNode(CellState state);
        Node * getLiveNode();
        Node * getDeadNode();
    private:
        static void checkValidBoardSize(const StartingBoardState& starting_state);
        Node * createNodeHelper(const StartingBoardState& starting_state,
                                unsigned row, unsigned col, int level);
        Node * getEmptyNodeAtLevelHelper(int level);
    private:
        shared_ptr<NodeStorage> node_storage;
        std::unordered_map<int, Node*> empty_nodes;
    };
}



#endif //GAMEOFLIFE_NODEFACTORY_H
