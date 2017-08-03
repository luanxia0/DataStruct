//
// Created by magicsun on 16-3-11.
//

#ifndef DATASTRUCTURE_SPLAY_H
#define DATASTRUCTURE_SPLAY_H

#include "BST.h"
namespace sy
{

    template <typename T>
    class Splay : public sy::BST<T>
    {
    protected:
        BinNodePosi(T) splay(BinNodePosi(T) v);

        void attachAsLChild(BinNodePosi(T) p, BinNodePosi(T) c);
        void attachAsRChild(BinNodePosi(T) p, BinNodePosi(T) c);

    public:
        BinNodePosi(T) &search(const T &e);
        BinNodePosi(T) insert(const T &e);
        bool remove(const T &e);

    };

    template <typename T>
	BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
    {
        if(!v)
        {
            return nullptr;
        }
        BinNodePosi(T) p = nullptr;
        BinNodePosi(T) g = nullptr;
        while((p = v->parent) && (g = p->parent))
        {
            BinNodePosi(T) gg = g->parent;
            if(IsLChild(*v))
            {
                if(IsLChild(*p))//zig-zig
                {
                    attachAsLChild(g, p->rc);
                    attachAsLChild(p, v->rc);
                    attachAsRChild(p, g);
                    attachAsRChild(v, p);
                }
                else
                {
                    attachAsLChild(p, v->rc);
                    attachAsRChild(g, v->lc);
                    attachAsLChild(v, g);
                    attachAsRChild(v, p);
                }
            }
            else if(IsRChild(*p))
            {
                attachAsRChild(g, p->lc);
                attachAsRChild(p, v->lc);
                attachAsLChild(p, g);
                attachAsLChild(v, p);
            }
            else
            {
                attachAsRChild(p, v->lc);
                attachAsLChild(g, v->rc);
                attachAsRChild(v, g);
                attachAsLChild(v, p);
            }

            if(!gg)
            {
                v->parent = nullptr;
            }
            else
            {
                (g == gg->lc)? attachAsLChild(gg, v) : attachAsRChild(gg, v);
            }
            this->updateHeight(g);
            this->updateHeight(p);
            this->updateHeight(v);
        }

        if(p = v->parent)
        {
            if(IsLChild(*v))
            {
                attachAsLChild(p, v->rc);
                attachAsRChild(v, p);
            }
            else
            {
                attachAsRChild(p, v->lc);
                attachAsLChild(v, p);
            }
            this->updateHeight(p);
            this->updateHeight(v);
        }
        v->parent = nullptr;
        return v;
    }

    template <typename T>
	BinNodePosi(T) &Splay<T>::search(const T &e)
    {
        BinNodePosi(T) p = this->searchIn(this->_root, e, this->_hot = nullptr);

        this->_root = splay(p ? p : this->_hot);
        return this->_root;

    }

    template <typename T>
	BinNodePosi(T) Splay<T>::insert(const T &e)
    {

        if(!this->_root)//处理空树的情况
        {
            this->_size++;
            return this->_root = new BinNode<T>(e);
        }

        if(e == search(e)->data)//如果结点已经存在了
        {
            return this->_root;
        }
        ++this->_size;
        BinNodePosi(T) t = this->_root;
        if(this->_root->data < e)
        {
            t->parent = this->_root = new BinNode<T>(e, nullptr, t, t->rc);
            if(HasRChild(*t))//更新右边子树的信息
            {
                t->rc->parent = this->_root;
                t->rc = nullptr;
            }
        }
        else
        {
            t->parent = this->_root = new BinNode<T>(e, nullptr, t->lc, t);
            if(HasLChild(*t))
            {
                t->lc->parent = this->_root;
                t->lc = nullptr;
            }
        }
        this->updateHeight(t);
        return this->_root;
    }

    template <typename T>
    bool Splay<T>::remove(const T &e)
    {
        if(!this->_root || (e != search(e)->data))
        {
            return false;
        }
        BinNodePosi(T) w = this->_root;

        if(!HasLChild(*(this->_root)))
        {
            this->_root = this->_root->rc;
            if(this->_root)
            {
                this->_root->parent = nullptr;
            }
        }
        else if(!HasRChild(*(this->_root)))
        {
            this->_root = this->_root->lc;
            if(this->_root)
            {
                this->_root->parent = nullptr;
            }
        }
        else
        {
            BinNodePosi(T) lTree = this->_root->lc;
            lTree->parent = nullptr;
            this->_root->lc = nullptr;
            this->_root = this->_root->rc;
            this->_root->parent = nullptr;
            search(w->data);
            this->_root->lc = lTree;
            lTree->parent = this->_root;
        }
        delete w;
        --this->_size;
        if(this->_root)
        {
            this->updateHeight(this->_root);
        }
        return true;
    }

    template <typename T>
    void Splay<T>::attachAsLChild(BinNodePosi(T) p, BinNodePosi(T) c)
    {
        if(p)
        {
            p->lc = c;
        }
        if(c)
        {
            c->parent = p;
        }
    }

    template <typename T>
    void Splay<T>::attachAsRChild(BinNodePosi(T) p, BinNodePosi(T) c)
    {
        if(p)
        {
            p->rc = c;
        }
        if(c)
        {
            c->parent = p;
        }
    }
}


#endif //DATASTRUCTURE_SPLAY_H


