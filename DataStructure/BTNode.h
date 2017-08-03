//
// Created by magicsun on 16-3-19.
//

#ifndef DATASTRUCTURE_BTNODE_H
#define DATASTRUCTURE_BTNODE_H
#include "Vector.h"
namespace sy
{
#define BTNodePosi(T) BTNode<T>*
    template <typename T>
    struct BTNode
    {
        BTNodePosi(T) parent;
        sy::Vector<T> key;
        sy::Vector<BTNodePosi(T)> child;
        BTNode(){parent = nullptr; child.insert(0, nullptr);}
        BTNode(const T &e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr)
        {
            parent = nullptr;
            key.insert(0, e);
            child.insert(0, lc);
            child.insert(1, rc);
            if(lc)
            {
                lc->parent = this;
            }
            if(rc)
            {
                rc->parent = this;
            }
        }
    };
}
#endif //DATASTRUCTURE_BTNODE_H
