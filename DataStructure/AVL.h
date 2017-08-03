//
// Created by magicsun on 16-3-6.
//

#ifndef DATASTRUCTURE_AVL_H
#define DATASTRUCTURE_AVL_H

#include "BST.h"
#define Balanced(x) (stature((x).lc) == stature((x).rc))

#define BalFac(x) (stature((x).lc) - stature((x).rc))

#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))
//
#define tallerChild(x) ( \
(stature((x)->lc) > stature((x)->rc)) ? (x)->lc : (\
(stature((x)->rc) > stature((x)->lc)) ? (x)->rc : (\
(IsLChild(*x)) ? (x)->lc : (x)->rc \
)\
)\
)



namespace sy
{

    template <typename T>
    class AVL : public sy::BST<T>
    {
    public:
        virtual BinNodePosi(T) insert(const T &);
        virtual bool remove(const T &);

    protected:
        BinNodePosi(T) rotateAt(BinNodePosi(T) v);
//        BinNodePosi(T) tallerChild(BinNodePosi(T) &g);
    };

    template <typename T>
    BinNode<T> *AVL<T>::insert(const T &e)
    {
        BinNodePosi(T) &newNode = this->search(e);
        if(nullptr != newNode)
        {
            return newNode;
        }
        newNode = new BinNode<T>(e, this->_hot);
        ++this->_size;
        for(BinNodePosi(T) g = newNode->parent; nullptr != g; g = g->parent)
        {
            if(!AvlBalanced(*g))
            {
                BinNodePosi(T) &tmp = FromParentTo(*g);
                tmp = rotateAt(tallerChild(tallerChild(g)));
                break;
            }
            else
            {
                this->updateHeight(g);
            }

        }
        return newNode;

    }

    template <typename T>
    bool AVL<T>::remove(const T &e)
    {
        BinNodePosi(T) &x = this->search(e);
        if(!x)
        {
            return false;
        }
        this->removeAt(x, this->_hot);
        this->_size--;
        for(BinNodePosi(T) g = this->_hot; nullptr != g; g = g->parent)
        {
            if(!AvlBalanced(*g))
            {
                g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            }
            this->updateHeight(g);
        }
        return true;
    }

    template <typename T>
    BinNode<T> *AVL<T>::rotateAt(BinNode<T> *v)
    {
        BinNodePosi(T) p = v->parent;
        BinNodePosi(T) g = p->parent;

        if(IsLChild(*p))//zig
        {
            if(IsLChild(*v))//zig-zig
            {
                p->parent = g->parent;
                return this->connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
            }
            else//zig-zag
            {
                v->parent = g->parent;
                return  this->connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
            }
        }
        else//zag
        {
            if(IsRChild(*v))//zag-zag
            {
                p->parent = g->parent;
                return this->connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
            }
            else//zag-zig
            {
                v->parent = g->parent;
                return  this->connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
            }

        }
    }

//    template <typename T>
//    inline BinNode<T> *AVL<T>::tallerChild(BinNode<T> *&g)
//    {
//        if(stature(g->lc) > stature(g->rc))
//        {
//            return  g->lc;
//        }
//        if(stature(g->rc) > stature(g->lc))
//        {
//            return g->rc;
//        }
//        if(IsLChild(*g))
//        {
//            return g->lc;
//        }
//        return g->rc;
//    }
}

#endif //DATASTRUCTURE_AVL_H
