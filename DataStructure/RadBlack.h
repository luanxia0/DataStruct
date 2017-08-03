//
// Created by magicsun on 16-3-26.
//

#ifndef DATASTRUCTURE_RADBLACK_H
#define DATASTRUCTURE_RADBLACK_H

#include "BST.h"
#include "AVL.h"
#include <cstdlib>

namespace sy
{
    template <typename T>
    class RedBlcak : public sy::AVL<T>
    {
    private:
        inline bool isBlack(const BinNodePosi(T) p);
        inline bool isRed(const BinNodePosi(T) p);
        inline bool blackHeightUpdated(const BinNodePosi(T) p);
    protected:
        void solveDoubleRed(BinNodePosi(T) v);
        void solveDoubleBlack(BinNodePosi(T) v);
        int updateHeight(BinNodePosi(T) v);
    public:
        BinNodePosi(T) insert(const T &e);
        bool remove(const T &e);
    };

    template <typename T>
    bool RedBlcak<T>::isBlack(const BinNode<T> *p)
    {
        return (!p || RB_BLACK == p->color);
    }

    template <typename T>
    bool RedBlcak<T>::isRed(const BinNode<T> *p)
    {
        return !isBlack(p);
    }

    template <typename T>
    bool RedBlcak<T>::blackHeightUpdated(const BinNode<T> *p)
    {
        return (stature((*p).lc) == stature((*p).rc)) && \
                (*p).height == (isRed(p) ? stature((*p).lc) : stature((*p).rc) + 1);
    }

    template <typename T>
    void RedBlcak<T>::solveDoubleRed(BinNode<T> *v)
    {
        if( IsRoot(*v) )
        {
            this->_root->color = RB_BLACK;
            this->_root->height++;
            return;
        }

        BinNodePosi(T) p = v->parent;
        if(isBlack(p))
        {
            return;
        }

        BinNodePosi(T) g = p->parent;
        BinNodePosi(T) u = uncle(v);
        if(isBlack(u))
        {
            if(IsLChild(*v) == IsLChild(*p))//
            {
                p->color = RB_BLACK;
            }
            else
            {
                v->color = RB_BLACK;
            }
            g->color = RB_RED;

            BinNodePosi(T) gg = g->parent;
            BinNodePosi(T) r = FromParentTo(*g) = this->rotateAt(v);
            r->parent = gg;
        }
        else
        {
            p->color = RB_BLACK;
            p->height++;
            u->color = RB_BLACK;
            u->height++;
            if(!IsRoot(*g))
            {
                g->color = RB_RED;
            }
            solveDoubleRed(g); 
        }
    }

    template <typename T>
    void RedBlcak<T>::solveDoubleBlack(BinNode<T> *r)
    {
		BinNodePosi(T) p = r ? r->parent : this->_hot;
		if (!p)
		{
			return;
		}
		BinNodePosi(T) s = (r == p->lc)? p->rc : p->lc;

		if (isBlack(s))
		{
			BinNodePosi(T) t = nullptr;
			if (isRed(s->rc))
			{
				t = s->rc;
			}
			if (isRed(s->lc))
			{
				t = s->lc;
			}

			if (t)
			{
				RBColor oldColor = p->color;
				BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);

				if (HasLChild(*b))
				{
					b->lc->color = RB_BLACK;
					updateHeight(b->lc);
				}
				if (HasRChild(*b))
				{
					b->rc->color = RB_BLACK;
					updateHeight(b->rc);
				}

				b->color = oldColor;
				updateHeight(b);
			}
			else
			{
				s->color = RB_RED;
				s->height--;
				if (isRed(p))
				{
					p->color = RB_BLACK;
				}
				else
				{
					p->height--;
					solveDoubleBlack(p);
				}
			}
		}
		else
		{
			s->color = RB_BLACK;
			p->color = RB_RED;
			BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;
			_hot = p;
			FromParentTo(*p) = rotateAt(t);
			solveDoubleBlack(r);
		}
    }

    template <typename T>
    int RedBlcak<T>::updateHeight(BinNode<T> *v)
    {
        v->height = Max(stature(v->lc), stature(v->rc));

        return isBlack(v) ? v->height++ : v->height;
    }

    template <typename T>
    BinNode<T> *RedBlcak<T>::insert(const T &e)
    {
        BinNodePosi(T) &x = this->search(e);
        //if exist
        if(x)
        {
            return x;
        }

        x = new BinNode<T>(e, _hot, nullptr, nullptr, -1);

        solveDoubleRed(x);

        this->_size++;

        return x ? x : this->_hot->parent;

    }

    template <typename T>
    bool RedBlcak<T>::remove(const T &e)
    {
        BinNodePosi(T) &x = this->search(e);
        if(!x)
        {
            return  false;
        }

        BinNodePosi(T) r = this->removeAt(x, this->_hot);
        if(!(--this->_size))
        {
            return true;
        }

        if(!this->_hot)
        {
            this->_root->color = RB_BLACK;
            this->updateHeight(this->_root);
            return true;
        }

        if(blackHeightUpdated(this->_hot))
        {
            return true;
        }

        if(isRed(r))
        {
            r->color = RB_BLACK;
            r->height++;
            return true;
        }

        solveDoubleBlack(r);
        return true;


    }


}

#endif //DATASTRUCTURE_RADBLACK_H
