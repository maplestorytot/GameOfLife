//
// Created by ryan on 24/05/22.
//

#include "../../include/hash_life/Node.h"
#include <stdexcept>
#include <iostream>
#include "../../include/Board.h"
#include <math.h>
namespace GameOfLife {
    Node::Node(Node * nw, Node * ne, Node * sw, Node * se, int level):
            nw(nw), ne(ne), sw(sw), se(se), level(level), cached_next_gen(nullptr),
            nw_cached_mirror({}), ne_cached_mirror({}), sw_cached_mirror({}), se_cached_mirror({}){}

    Node * Node::get_nw() const{
        return nw;
    }

    Node * Node::get_ne() const{
        return ne;
    }

    Node * Node::get_sw() const{
        return sw;
    }

    Node * Node::get_se() const{
        return se;
    }

    int Node::get_level() const{
        return level;
    }

    Node * Node::get_cached_next_gen() const{
        return cached_next_gen;
    }

    Node * Node::set_cached_next_gen(Node * next_gen){
        cached_next_gen = next_gen;
        return cached_next_gen;
    }

    Node::Mirror Node::get_cached_mirror(Node::CoreOrientation orientation){
        if(orientation == NW){
            return nw_cached_mirror;
        } else if(orientation == NE){
            return ne_cached_mirror;
        } else if(orientation == SW){
            return sw_cached_mirror;
        } else if(orientation == SE){
            return se_cached_mirror;
        }
        throw std::invalid_argument("Invalid Mirror Orientation while Getting!");
    }

    void Node::set_cached_mirror(Node::CoreOrientation orientation, Mirror mirror){
        if(orientation == NW){
            nw_cached_mirror = mirror;
            return;
        } else if(orientation == NE){
            ne_cached_mirror = mirror;
            return;
        } else if(orientation == SW){
            sw_cached_mirror = mirror;
            return;
        } else if(orientation == SE){
            se_cached_mirror = mirror;
            return;
        }
        throw std::invalid_argument("Invalid Mirror Orientation while Setting!");
    }

/*
    Node * Node::get_quad_value(Node::CoreOrientation orientation){
        if(orientation == NW){
            return nw;
        } else if(orientation == NE){
            return ne;
        } else if(orientation == SW){
            return sw;
        } else if(orientation == SE){
            return se;
        }
        throw std::invalid_argument("Invalid Mirror Orientation while Get Quad Value!");
    }
*/

}  // namespace GameOfLife