//
// Created by ryan on 25/05/22.
//

#include "../../include/hash_life/NextNodeGenerationTransformer.h"
#include <iostream>
#include <gsl/gsl>

namespace GameOfLife {
    NextNodeGenerationTransformer::NextNodeGenerationTransformer(std::shared_ptr<NodeFactory> factory):
        node_factory(factory), printer({node_factory}){

    }

    Node * NextNodeGenerationTransformer::centeredSubnode(const Node * node) {
        return node_factory->getOrCreateNode(node->get_nw()->get_se(), node->get_ne()->get_sw(),
                                             node->get_sw()->get_ne(), node->get_se()->get_nw());
    }
    Node * NextNodeGenerationTransformer::centeredHorizontal(const Node * w, const Node * e) {
        return node_factory->getOrCreateNode(w->get_ne()->get_se(), e->get_nw()->get_sw(), w->get_se()->get_ne(), e->get_sw()->get_nw());
    }
    Node * NextNodeGenerationTransformer::centeredVertical(const Node * n, const Node * s) {
        return node_factory->getOrCreateNode(n->get_sw()->get_se(), n->get_se()->get_sw(), s->get_nw()->get_ne(), s->get_ne()->get_nw());
    }

    Node * NextNodeGenerationTransformer::centeredSubSubnode(const Node * node) {
        return node_factory->getOrCreateNode(node->get_nw()->get_se()->get_se(), node->get_ne()->get_sw()->get_sw(),
                                             node->get_sw()->get_ne()->get_ne(), node->get_se()->get_nw()->get_nw());
    }

    Node * NextNodeGenerationTransformer::nextGeneration(Node *node) {
        auto cached_next_gen = node->get_cached_next_gen();
        if (cached_next_gen){
            return cached_next_gen;
        }

        Node * next_gen = nullptr;
        if (node->get_level() == LEVEL_FOR_NORMAL_SIMULATION) {
            next_gen = normalSimulation(node);
        } else {
            auto nw = node->get_nw();
            auto ne = node->get_ne();
            auto sw = node->get_sw();
            auto se = node->get_se();

            auto n00 = centeredSubnode(nw),
                    n01 = centeredHorizontal(nw, ne),
                    n02 = centeredSubnode(ne),
                    n10 = centeredVertical(nw, sw),
                    n11 = centeredSubSubnode(node),
                    n12 = centeredVertical(ne, se),
                    n20 = centeredSubnode(sw),
                    n21 = centeredHorizontal(sw, se),
                    n22 = centeredSubnode(se);

            next_gen = node_factory->getOrCreateNode(
                    nextGeneration(node_factory->getOrCreateNode(n00, n01, n10, n11)),
                    nextGeneration(node_factory->getOrCreateNode(n01, n02, n11, n12)),
                    nextGeneration(node_factory->getOrCreateNode(n10, n11, n20, n21)),
                    nextGeneration(node_factory->getOrCreateNode(n11, n12, n21,  n22)));
        }
        Expects(node->get_cached_next_gen() == nullptr);
        return node->set_cached_next_gen(next_gen);
    }
/*    Node * NextNodeGenerationTransformer::nextGeneration(Node *node) {
        auto cached_next_gen = node->get_cached_next_gen();
        if (cached_next_gen){
            return cached_next_gen;
        }

        Node * next_gen = nullptr;
        if (node->get_level() == LEVEL_FOR_NORMAL_SIMULATION) {
            next_gen = normalSimulation(node);
        } else {
            auto nw = node->get_nw();
            auto ne = node->get_ne();
            auto sw = node->get_sw();
            auto se = node->get_se();

            auto n00 = nextGeneration(nw),
                    n01 = horizontalForward(nw, ne),
                    n02 = nextGeneration(ne),
                    n10 = verticalForward(nw, sw),
                    n11 = centeredForward(node),
                    n12 = verticalForward(ne, se),
                    n20 = nextGeneration(sw),
                    n21 = horizontalForward(sw, se),
                    n22 = nextGeneration(se);

            next_gen = node_factory->getOrCreateNode(
                    nextGeneration(node_factory->getOrCreateNode(n00, n01, n10, n11)),
                    nextGeneration(node_factory->getOrCreateNode(n01, n02, n11, n12)),
                    nextGeneration(node_factory->getOrCreateNode(n10, n11, n20, n21)),
                    nextGeneration(node_factory->getOrCreateNode(n11, n12, n21,  n22)));
        }
        Expects(node->get_cached_next_gen() == nullptr);
        return node->set_cached_next_gen(next_gen);
    }

    Node * NextNodeGenerationTransformer::horizontalForward(const Node * w, const Node * e) {
        return nextGeneration(node_factory->getOrCreateNode(w->get_ne(),
                                                             e->get_nw(), w->get_se(), e->get_sw()));
    }
    Node * NextNodeGenerationTransformer::verticalForward(const Node * n, const Node * s) {
        return nextGeneration(node_factory->getOrCreateNode(n->get_sw(),
                                                             n->get_se(), s->get_nw(), s->get_ne()));
    }
    Node * NextNodeGenerationTransformer::centeredForward(const Node * node) {
        return nextGeneration(node_factory->getOrCreateNode(node->get_nw()->get_se(),node->get_ne()->get_sw(),
                                                             node->get_sw()->get_ne(), node->get_se()->get_nw()));
    }
    */
    Node * NextNodeGenerationTransformer::normalSimulation(const Node * node){

        return node_factory->getOrCreateNode(advanceCell(Node::NW, node, node_factory->getLiveOrDeadNode(node->get_nw()->get_se())),
                                             advanceCell(Node::NE, node, node_factory->getLiveOrDeadNode(node->get_ne()->get_sw())),
                                             advanceCell(Node::SW, node, node_factory->getLiveOrDeadNode(node->get_sw()->get_ne())),
                                             advanceCell(Node::SE, node, node_factory->getLiveOrDeadNode(node->get_se()->get_nw())));
    }

    Node * NextNodeGenerationTransformer::advanceCell(Node::CoreOrientation orientation, const Node * node, CellState current_value) {
        // TODO Check shared pointer equality
        auto liveNeighbors = countLiveNeighbors(orientation, node);
//        auto current_value = node_factory->getLiveOrDeadNode(node->get_quad_value(orientation).opposite);
//        std::cout<<"neighbors"<<liveNeighbors<<",ori:"<<orientation<<std::endl;
        if((liveNeighbors == 0 || liveNeighbors == 1) && current_value == LIVE){
            return node_factory->getDeadNode();
        }else if(liveNeighbors == 2){
            return node_factory->getLiveOrDeadNode(current_value);
        }else if(liveNeighbors == 3 && current_value == DEAD){
            return node_factory->getLiveNode();
        }else if(liveNeighbors >= 4 && current_value == LIVE){
            return node_factory->getDeadNode();
        }
        return node_factory->getLiveOrDeadNode(current_value);
//        throw std::invalid_argument("Invalid advanceCell!");
    }


    int NextNodeGenerationTransformer::countLiveNeighbors(Node::CoreOrientation orientation, const Node * node) {
        // TODO CHECK!
//        printer.print(node);
        if(orientation == Node::NW){
            return node_factory->getLiveOrDeadNode(node->get_nw()->get_nw()) +
                    node_factory->getLiveOrDeadNode(node->get_nw()->get_ne()) +
                    node_factory->getLiveOrDeadNode(node->get_nw()->get_sw()) +
                    node_factory->getLiveOrDeadNode(node->get_sw()->get_nw()) +
                    node_factory->getLiveOrDeadNode(node->get_sw()->get_ne()) +
                    node_factory->getLiveOrDeadNode(node->get_ne()->get_nw()) +
                    node_factory->getLiveOrDeadNode(node->get_ne()->get_sw()) +
                    node_factory->getLiveOrDeadNode(node->get_se()->get_nw());
        } else if(orientation == Node::NE){
            return node_factory->getLiveOrDeadNode(node->get_nw()->get_ne()) +
                   node_factory->getLiveOrDeadNode(node->get_nw()->get_se()) +
                   node_factory->getLiveOrDeadNode(node->get_ne()->get_nw()) +
                   node_factory->getLiveOrDeadNode(node->get_ne()->get_ne()) +
                   node_factory->getLiveOrDeadNode(node->get_ne()->get_se()) +
                   node_factory->getLiveOrDeadNode(node->get_se()->get_nw()) +
                   node_factory->getLiveOrDeadNode(node->get_se()->get_ne()) +
                   node_factory->getLiveOrDeadNode(node->get_sw()->get_ne());
        } else if(orientation == Node::SW){
            return node_factory->getLiveOrDeadNode(node->get_nw()->get_sw()) +
                   node_factory->getLiveOrDeadNode(node->get_nw()->get_se()) +
                   node_factory->getLiveOrDeadNode(node->get_ne()->get_sw()) +
                   node_factory->getLiveOrDeadNode(node->get_sw()->get_nw()) +
                   node_factory->getLiveOrDeadNode(node->get_sw()->get_sw()) +
                   node_factory->getLiveOrDeadNode(node->get_sw()->get_se()) +
                   node_factory->getLiveOrDeadNode(node->get_se()->get_nw()) +
                   node_factory->getLiveOrDeadNode(node->get_se()->get_sw());
        } else if(orientation == Node::SE){
            return node_factory->getLiveOrDeadNode(node->get_nw()->get_se()) +
                   node_factory->getLiveOrDeadNode(node->get_ne()->get_sw()) +
                   node_factory->getLiveOrDeadNode(node->get_ne()->get_se()) +
                   node_factory->getLiveOrDeadNode(node->get_sw()->get_ne()) +
                   node_factory->getLiveOrDeadNode(node->get_sw()->get_se()) +
                   node_factory->getLiveOrDeadNode(node->get_se()->get_ne()) +
                   node_factory->getLiveOrDeadNode(node->get_se()->get_se()) +
                   node_factory->getLiveOrDeadNode(node->get_se()->get_sw());
        }
        throw std::invalid_argument("Invalid countLiveNeighbors!");
    }

    Node::Mirror NextNodeGenerationTransformer::createMirror(Node::CoreOrientation orientation, Node * node){
        if(node->get_cached_mirror(orientation).corner != nullptr){
            return node->get_cached_mirror(orientation);
        }
        Node::Mirror mirror = {};
        mirror.corner = getMirrorCorner(orientation, node);
        if(orientation == Node::NW){
            mirror.outright = getMirrorNorth(node);
            mirror.outleft = getMirrorWest(node);
        } else if(orientation == Node::NE){
            mirror.outright = getMirrorEast(node);
            mirror.outleft = getMirrorNorth(node);
        } else if(orientation == Node::SW){
            mirror.outright = getMirrorWest(node);
            mirror.outleft = getMirrorSouth(node);
        } else if(orientation == Node::SE){
            mirror.outright = getMirrorSouth(node);
            mirror.outleft = getMirrorEast(node);
        } else {
            throw std::invalid_argument("Invalid Mirror Orientation!");
        }
        node->set_cached_mirror(orientation, mirror);
        return mirror;
    }
    Node * NextNodeGenerationTransformer::getMirrorCorner(Node::CoreOrientation orientation, Node * node) {
        if(node->get_level() == 0){
            return node;
        }
        if(orientation == Node::NW){
            return node_factory->getOrCreateNode(getMirrorCorner(orientation, node->get_nw()),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1));
        } else if(orientation == Node::NE){
            return node_factory->getOrCreateNode(node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 getMirrorCorner(orientation, node->get_ne()),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1));
        } else if(orientation == Node::SW){
            return node_factory->getOrCreateNode(node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 getMirrorCorner(orientation, node->get_sw()),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1));
        } else if(orientation == Node::SE){
            return node_factory->getOrCreateNode(node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                                                 getMirrorCorner(orientation, node->get_se()));
        }
        throw std::invalid_argument("Invalid Mirror Orientation!");

    }
    Node * NextNodeGenerationTransformer::getMirrorNorth(Node * node){
        if(node->get_level() == 1){
            return node_factory->getOrCreateNode(node->get_nw(), node->get_ne(),
                                                 node_factory->getDeadNode(), node_factory->getDeadNode());
        }
        return node_factory->getOrCreateNode(
                getMirrorNorth(node->get_nw()), getMirrorNorth(node->get_ne()),
                node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                node_factory->getEmptyNodeAtLevel(node->get_level() - 1));
    }

    Node * NextNodeGenerationTransformer::getMirrorSouth(Node * node){
        if(node->get_level() == 1){
            return node_factory->getOrCreateNode(node_factory->getDeadNode(), node_factory->getDeadNode(),
                                                 node->get_sw(), node->get_se());
        }
        return node_factory->getOrCreateNode(
                node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                getMirrorSouth(node->get_sw()), getMirrorSouth(node->get_se()));
    }

    Node * NextNodeGenerationTransformer::getMirrorEast(Node * node){
        if(node->get_level() == 1){
            return node_factory->getOrCreateNode(node_factory->getDeadNode(),
                                                 node->get_ne(),
                                                 node_factory->getDeadNode(),
                                                 node->get_se());
        }
        return node_factory->getOrCreateNode(
                node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                getMirrorEast(node->get_ne()),
                node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                getMirrorEast(node->get_se()));
    }

    Node * NextNodeGenerationTransformer::getMirrorWest(Node * node){
        if(node->get_level() == 1){
            return node_factory->getOrCreateNode( node->get_nw(), node_factory->getDeadNode(),
                                                node->get_sw(),node_factory->getDeadNode());
        }
        return node_factory->getOrCreateNode(
                getMirrorWest(node->get_nw()),
                node_factory->getEmptyNodeAtLevel(node->get_level() - 1),
                getMirrorWest(node->get_sw()),
                node_factory->getEmptyNodeAtLevel(node->get_level() - 1));
    }
}  // namespace GameOfLife