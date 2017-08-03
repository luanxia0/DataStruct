//
// Created by magicsun on 16-3-5.
//

#ifndef DATASTRUCTURE_BST_H
#define DATASTRUCTURE_BST_H
#include "BinaryTree.h"

namespace sy
{
    template <typename T>
    class BST : public sy::BinaryTree<T>
    {
    protected:
        BinNodePosi(T) &searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot);
        BinNodePosi(T) _hot;
        BinNodePosi(T) connect34(BinNodePosi(T) , BinNodePosi(T), BinNodePosi(T),
                                 BinNodePosi(T) , BinNodePosi(T), BinNodePosi(T),
                                 BinNodePosi(T));
        BinNodePosi(T) removeAt(BinNodePosi(T) &, BinNodePosi(T)&);

    public:
        virtual BinNodePosi(T) &search(const T & );
        virtual BinNodePosi(T) insert(const T &);
        virtual bool remove(const T &);

    };

    template <typename T>
	BinNodePosi(T) &BST<T>::searchIn(BinNodePosi(T) &root, const T &e, BinNodePosi(T) &hot)
    {
        if((nullptr == root) || (root->data == e))
        {
            return root;
        }
        hot = root;

        if(e < root->data)
        {
            return searchIn(root->lc, e, hot);
        }
        else
        {
            return searchIn(root->rc, e, hot);
        }
    }

    template <typename T>
	BinNodePosi(T)&BST<T>::search(const T &e)
    {
        return searchIn(this->_root, e, _hot = nullptr);
    }

    template <typename T>
	BinNodePosi(T) BST<T>::insert(const T &e)
    {
        BinNodePosi(T) &curNode = search(e);
        if(nullptr != curNode)
        {
            return curNode;
        }
        curNode = new BinNode<T>(e, _hot);
        ++this->_size;
        this->updateHeightAbove(curNode);
        return curNode;
    }

    template <typename T>
    bool BST<T>::remove(const T &e)
    {
        BinNodePosi(T) &node = search(e);
        if(nullptr == node)
        {
            return false;
        }
        removeAt(node, _hot);
        --this->_size;
        this->updateHeightAbove(_hot);
        return true;
    }

    template <typename T>
	BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T) &delNode, BinNodePosi(T) &hot)
    {
        BinNodePosi(T) actualDelNode = delNode;
        BinNodePosi(T) succ = nullptr;
        if(!HasLChild(*delNode))
        {
            succ = delNode = delNode->rc;
        }
        else if(!HasRChild(*delNode))
        {
            succ = delNode = delNode->lc;
        }
        else
        {
            actualDelNode = actualDelNode->succ();
            Swap(delNode->data, actualDelNode->data);
            BinNodePosi(T) parent = actualDelNode->parent;

            //实际被删除的点的后继只能有单分支，且该分支是右孩子,因为succ返回的是最左边的点了
            //只有actualDelNode 是delNode的右孩子
            ((parent == delNode) ? parent->rc : parent->lc) = succ = actualDelNode->rc;
        }

        hot = actualDelNode->parent;
        if(nullptr != succ)
        {
            succ->parent = hot;
        }
        delete actualDelNode;
        return succ;//返回后继的结点，在这个位置上的点
    }

    template <typename T>
	BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, BinNodePosi(T) T0,
		BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
    {
        a->lc = T0;
        if(T0)
        {
            T0->parent = a;
        }
        a->rc = T1;
        if(T1)
        {
            T1->parent = a;
        }
        this->updateHeight(a);

        c->lc = T2;
        if(T2)
        {
            T2->parent = c;
        }
        c->rc = T3;
        if(T3)
        {
            T3->parent = c;
        }
        this->updateHeight(c);

        b->lc = a;
        b->rc = c;
        a->parent = b;
        c->parent = b;
        this->updateHeight(b);
        return b;
    }
}


#endif //DATASTRUCTURE_BST_H
