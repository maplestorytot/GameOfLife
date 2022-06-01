//
// Created by ryan on 24/05/22.
//

#ifndef GAMEOFLIFE_NODESTORAGE_H
#define GAMEOFLIFE_NODESTORAGE_H
#include "Node.h"
#include <unordered_map>
#include <string>
#include <boost/optional.hpp>
#include <functional>
#include <boost/container_hash/hash.hpp>

namespace GameOfLife {

    struct StorageKey {
        Node * nw;
        Node * ne;
        Node * sw;
        Node * se;
    };

    class NodeStorage {
    public:
        NodeStorage();
        boost::optional<Node *> getNode(StorageKey key);
        Node * getDeadNode();
        Node * getLiveNode();
        Node * storeNode(Node node);
        void printStorage();
    private:
        boost::hash<std::array<Node*, 4>> hasher;
        std::vector<std::unordered_map<uint64_t, std::shared_ptr<Node>>> nodes;
    };

}

#endif //GAMEOFLIFE_NODESTORAGE_H
