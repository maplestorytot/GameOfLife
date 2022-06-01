//
// Created by ryan on 30/05/22.
//

#ifndef GAMEOFLIFE_NODEPRINTER_H
#define GAMEOFLIFE_NODEPRINTER_H
#include "NodeFactory.h"

namespace GameOfLife {
    class NodePrinter {
    public:
        NodePrinter(std::shared_ptr<NodeFactory> node_factory);
        void print(const Node* node);
//    private:
        void printHelper(StartingBoardState& board, const Node* node, unsigned row, unsigned col);
    private:
        std::shared_ptr<NodeFactory> node_factory;
    };
}  // namespace GameOfLife



#endif //GAMEOFLIFE_NODEPRINTER_H
