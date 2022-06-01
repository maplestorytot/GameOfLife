//
// Created by ryan on 24/05/22.
//

#ifndef GAMEOFLIFE_NODE_H
#define GAMEOFLIFE_NODE_H
#include <memory>
#include "../Board.h"

namespace GameOfLife {
    using std::shared_ptr;
    class Node {
    public:
        struct Mirror {
            Node * corner;
            Node * outleft;
            Node * outright;
        };

        enum CoreOrientation {NW, NE, SW, SE};

        Node(Node * nw, Node * ne, Node * sw, Node * se, int level);
        Node * get_nw() const;
        Node * get_ne() const;
        Node * get_sw() const;
        Node * get_se() const;
        int get_level() const;
        Node * get_cached_next_gen() const;
        Node * set_cached_next_gen(Node * next_gen);
        Mirror get_cached_mirror(Node::CoreOrientation orientation);
        void set_cached_mirror(Node::CoreOrientation orientation, Mirror mirror);
    private:
        Node * cached_next_gen;
        Mirror nw_cached_mirror;
        Mirror ne_cached_mirror;
        Mirror sw_cached_mirror;
        Mirror se_cached_mirror;
        Node * nw;
        Node * ne;
        Node * sw;
        Node * se;
        int level;
    };
}  // namespace GameOfLife



#endif //GAMEOFLIFE_NODE_H
