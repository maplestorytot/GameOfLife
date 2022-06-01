//
// Created by ryan on 24/05/22.
//

#include "../../include/hash_life/NodeStorage.h"
#include <gsl/gsl>
#include <iostream>
namespace GameOfLife {
    static const uint64_t DEAD_KEY = 0;
    static const uint64_t LIVE_KEY = 1;

//    std::string StorageKey::get_value(){
//        std::hash<Node*> hasher;
//        auto val = hasher(nw);
//        return std::to_string((int64_t) nw) + std::to_string((int64_t) ne) +
//                std::to_string((int64_t) sw) + std::to_string((int64_t) se);
//    }

    NodeStorage::NodeStorage() {
        // TODO FIX 50
        nodes.resize(100);
        nodes[0][DEAD_KEY] = std::make_shared<Node>(nullptr, nullptr, nullptr, nullptr, 0);
        nodes[0][LIVE_KEY] = std::make_shared<Node>(nullptr, nullptr, nullptr, nullptr, 0);
    }

    boost::optional<Node *> NodeStorage::getNode(StorageKey key){
        auto& nodes_iterator = nodes[key.nw->get_level() + 1];
        auto value = nodes_iterator.find(hasher({key.nw, key.ne, key.sw, key.se}));
        if(value != nodes_iterator.end()){
            Expects(
                    key.nw == value->second->get_nw() &&
                    key.ne == value->second->get_ne() &&
                    key.sw == value->second->get_sw()&&
                    key.se == value->second->get_se()
            );
            return value->second.get();
        }
        return boost::none;
    }

    Node * NodeStorage::getLiveNode(){
        return nodes[0][LIVE_KEY].get();
    }

    Node * NodeStorage::getDeadNode() {
        return nodes[0][DEAD_KEY].get();
    }

// TODO CHECK
    Node * NodeStorage::storeNode(Node node) {
        auto& nodes_iterator = nodes[node.get_level()];
        StorageKey key = {node.get_nw(), node.get_ne(), node.get_sw(), node.get_se()};
        auto key_value = hasher({node.get_nw(), node.get_ne(), node.get_sw(), node.get_se()});
        Expects(nodes_iterator.find(key_value) == nodes_iterator.end());
        nodes_iterator[key_value] = std::make_shared<Node>(key.nw, key.ne, key.sw, key.se, node.get_level());
        auto val = nodes_iterator[key_value].get();
        return val;
    }

    void NodeStorage::printStorage(){
        int lvl = 0;
        for(const auto & set : nodes){
            if(set.empty() == false){
                std::cout<<"LEVEL: "<<lvl<<std::endl;
                for(const auto & kv : set){
                    std::cout<<kv.first<<","<<kv.second<<std::endl;
                }
            }

            lvl++;
        }
    }

}  // namespace GameOfLife