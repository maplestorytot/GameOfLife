//
// Created by ryan on 25/05/22.
//

#ifndef GAMEOFLIFE_NEXTNODEGENERATIONTRANSFORMER_H
#define GAMEOFLIFE_NEXTNODEGENERATIONTRANSFORMER_H
#include "NodeFactory.h"
#include "NodePrinter.h"
#define LEVEL_FOR_NORMAL_SIMULATION 2
namespace GameOfLife {
    class NextNodeGenerationTransformer {
    public:
        NextNodeGenerationTransformer(std::shared_ptr<NodeFactory> factory);
        Node * nextGeneration(Node* node);
        Node::Mirror createMirror(Node::CoreOrientation orientation, Node * node);
    private:
        Node * normalSimulation(const Node * node);
        Node * horizontalForward(const Node * w, const Node * e);
        Node * verticalForward(const Node * n, const Node * s);
        Node * centeredForward(const Node * node);
        Node * centeredHorizontal(const Node * w, const Node * e);
        Node * centeredVertical(const Node * n, const Node * s);
        Node * centeredSubSubnode(const Node * node);
        Node * centeredSubnode(const Node * node);

        Node * getMirrorCorner(Node::CoreOrientation orientation, Node * node);
        Node * getMirrorNorth(Node * node);
        Node * getMirrorSouth(Node * node);
        Node * getMirrorEast(Node * node);
        Node * getMirrorWest(Node * node);
        Node * advanceCell(Node::CoreOrientation orientation, const Node * node, CellState current_value);
        int countLiveNeighbors(Node::CoreOrientation orientation, const Node * node);
    private:
        std::shared_ptr<NodeFactory> node_factory;
        NodePrinter printer;

    };
}



#endif //GAMEOFLIFE_NEXTNODEGENERATIONTRANSFORMER_H
