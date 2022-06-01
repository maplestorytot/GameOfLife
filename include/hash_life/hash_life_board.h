//
// Created by ryan on 24/05/22.
//

#ifndef GAMEOFLIFE_HASH_LIFE_BOARD_H
#define GAMEOFLIFE_HASH_LIFE_BOARD_H
#include "../Board.h"
#include "NodeFactory.h"
#include "NextNodeGenerationTransformer.h"
#include "NodePrinter.h"

namespace GameOfLife {
    class HashLifeBoard : public IBoard {
    public:
        HashLifeBoard(StartingBoardState init_list, std::shared_ptr<NodeStorage> storage);

        void doAdvance() override;

        CellState operator[](const Coordinate &coordinate) override;

        void print() override;

        StartingBoardState convert() override;

    private:
        Node* createBorderAround(Node * nw, Node * ne, Node * sw,
                                            Node * se);
        void copyBorders();

    private:
        unsigned board_size;
        std::shared_ptr<NodeFactory> node_factory;
        NextNodeGenerationTransformer transformer;
        NodePrinter printer;
        Node * root;
        Node * empty_fourth;
    };
}

#endif //GAMEOFLIFE_HASH_LIFE_BOARD_H
