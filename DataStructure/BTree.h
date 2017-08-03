//
// Created by magicsun on 16-3-19.
//

#ifndef DATASTRUCTURE_BTREE_H
#define DATASTRUCTURE_BTREE_H
#include "BTNode.h"
namespace sy
{
    template <typename T>
    class BTree
    {
    protected:
        int _size;
        int _order;
        BTNodePosi(T) _root;
        BTNodePosi(T) _hot;
        void solveOverflow(BTNodePosi(T));
        void solveUnderflow(BTNodePosi(T));

        void release(BTNodePosi(T) v);
    public:
        BTree(int order = 3):_order(3), _size(0)
        {
            _root = new BTNode<T>();
        }
        virtual ~BTree(){if(_root) release (_root);}

        int const order() { return _order;}
        int const size() { return _size;}
        BTNodePosi(T) &root() { return _root; }
        bool empty() const { return !_root; }
        BTNodePosi(T) search(const T &e);
        bool insert(const T &e);
        bool remove(const T &e);
    };

    template <typename T>
    void BTree<T>::solveOverflow(BTNodePosi(T) v)
    {
        if (_order >= v->child.size())
        {
            return;
        }
        Rank s = _order / 2;
        BTNodePosi(T)newNode = new BTNode<T>();
        for (Rank i = 0; i < _order - s - 1; ++i)//
        {
            newNode->child.insert(i, v->child.remove(s + 1));
            newNode->key.insert(i, v->key.remove(s + 1));
        }

        newNode->child[_order - s - 1] = v->child.remove(s + 1);
        if (newNode->child[0])
        {
            for (Rank i = 0; i < _order - s; ++i)
            {
                newNode->child[i]->parent = newNode;
            }
        }
        BTNodePosi(T)p = v->parent;

        if (!p)
        {
            p = new BTNode<T>();
            _root = p;
            p->child[0] = v;
            v->parent = p;
        }

        Rank r  = 1 + p->key.search(v->key[0]);
        p->key.insert(r, v->key.remove(s));
        p->child.insert(r + 1, newNode);
        newNode->parent = p;
        solveOverflow(p);
    }

    template <typename T>
    void BTree<T>::solveUnderflow(BTNodePosi(T) v)
    {

        if((_order + 1) / 2 <= v->child.size())
        {
            return;
        }

        BTNodePosi(T) p = v->parent;
        if(!p)
        {
            if(!v->key.size() && v->child[0])
            {
                _root = v->child[0];
                _root->parent = nullptr;
                v->child[0] = nullptr;
                release(v);
            }
            return;
        }

        Rank r = 0;
        while(p->child[r] != v)
        {
            ++r;
        }
        if(0 < r)
        {
            BTNodePosi(T) ls = p->child[r - 1];
            if((_order + 1) / 2 < ls->child.size())
            {
                v->key.insert(0, p->key[r - 1]);
                p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
                v->child.insert(0, ls->child.remove(ls->child.size() - 1));

                if(v->child[0])
                {
                    v->child[0]->parent = v;
                }
                return;
            }
        }

        if(p->child.size() - 1 > r)
        {
            BTNodePosi(T) rs = p->child[r + 1];
            if( (_order + 1) / 2 < rs->child.size())
            {
                v->key.insert(v->key.size(), p->key[r]);
                p->key[r] = rs->key.remove(0);
                v->child.insert(v->child.size(), rs->child.remove(0));

                if(v->child[v->child.size() - 1])
                {
                    v->child[v->child.size() - 1]->parent = v;
                }
                return;
            }
        }

        if(0 < r)
        {
            BTNodePosi(T) ls = p->child[r - 1];
            ls->key.insert(ls->key.size(), p->key.remove(r - 1));
            p->child.remove(r);

            ls->child.insert(ls->child.size(), v->child.remove(0));
            if(ls->child[ls->child.size() - 1])
            {
                ls->child[ls->child.size() - 1]->parent = ls;
            }
            while(!v->key.empty())
            {
                ls->key.insert(ls->key.size(), v->key.remove(0));
                ls->child.insert(ls->child.size(), v->child.remove(0));

                if(ls->child[ls->child.size() - 1])
                {
                    ls->child[ls->child.size() - 1]->parent = ls;
                }
            }
            release(v);
        }
        else
        {
            BTNodePosi(T) rs = p->child[r + 1];
            rs->key.insert(0, p->key.remove(r));
            p->child.remove(r);
            rs->child.insert(0, v->child.remove(v->child.size() - 1));

            if(rs->child[0])
            {
                rs->child[0]->parent = rs;
            }
            while(!v->key.empty())
            {
                rs->key.insert(0, v->key.remove(v->key.size() - 1));
                rs->child.insert(0, v->child.remove(v->child.size() - 1));

                if(rs->child[0])
                {
                    rs->child[0]->parent = rs;
                }
            }

            release(v);

        }
        solveUnderflow(p);
        return;
    }

    template <typename T>
	BTNodePosi(T) BTree<T>::search(const T &e)
    {
        BTNodePosi(T) v = _root;
        _hot = nullptr;
        while(v)
        {
            Rank r = v->key.search(e);
            if((0 <= r) && (e == v->key[r]))
            {
                return v;
            }
            _hot = v;
            v = v->child[r + 1];
        }
        return nullptr;
    }

    template <typename T>
    bool BTree<T>::insert(const T &e)
    {
        BTNodePosi(T) v = search(e);
        if(v)
        {
            return false;
        }
        Rank r = _hot->key.search(e);
        _hot->key.insert(r + 1, e);
        _hot->child.insert(r + 2, nullptr);
        _size++;
        solveOverflow(_hot);
        return true;
    }

    template <typename T>
    bool BTree<T>::remove(const T &e)
    {
        BTNodePosi(T) v = search(e);
        if(!v)
        {
            return false;
        }
        Rank r = v->key.search(e);
        if(v->child[0])
        {
            BTNodePosi(T) u = v->child[r + 1];
            while(u->child[0])
            {
                u = u->child[0];
            }
            v->key[r] = u->key[0];
            v = u;
            r = 0;
        }
        v->key.remove(r);
        v->child.remove(r + 1);
        _size--;
        solveUnderflow(v);
        return true;
    }

    template <typename T>
    void BTree<T>::release(BTNodePosi(T) v)
    {
        delete(v);
    }


}
#endif //DATASTRUCTURE_BTREE_H
