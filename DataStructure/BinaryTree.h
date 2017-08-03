//
// Created by magicsun on 16-1-30.
//

#ifndef DATASTRUCTS_BINTREE_H
#define DATASTRUCTS_BINTREE_H


#include <iostream>
#include "BinaryTreeNode.h"
#include "Stack.h"
#include "Queue.h"
#include "Utility.h"
namespace sy
{
    template <typename T>
    class BinaryTree
    {
    protected:
        int _size;
        BinNodePosi(T) _root;

        virtual int updateHeight(BinNodePosi(T) x);
        void updateHeightAbove(BinNodePosi(T) x);
        void release(BinNodePosi(T) x);
        virtual int removeAt(BinNode<T> *pNode);

        template <typename VST>
        void visitAlongLeftBranch(BinNodePosi(T) tree, VST &visit, sy::Stack<BinNodePosi(T)> &traStack);

        void goAlongLeftBranch(BinNodePosi(T) tree, sy::Stack<BinNodePosi(T)> &traStack);
        void gotoHLVFL(sy::Stack<BinNodePosi(T)> &s);
    public:

        BinaryTree():_size(0), _root(nullptr) {}
        ~BinaryTree();

        //read-only
        int size() const { return  _size; }
        bool empty() const { return !_size; }
        BinNodePosi(T) root() { return _root; }

        //write
        BinNodePosi(T) insertAsRoot(const T &e);
        BinNodePosi(T) insertAsLeftChild(BinNodePosi(T) x, const T &e);
        BinNodePosi(T) insertAsRightChild(BinNodePosi(T) x, const T &e);
        BinNodePosi(T) attachAsLeftChild(BinNodePosi(T) x, BinaryTree<T> * &t);
        BinNodePosi(T) attachAsRightChild(BinNodePosi(T) x, BinaryTree<T> *&t);

        int remove(BinNodePosi(T) x);//

        BinaryTree<T> *secede(BinNodePosi(T) x);

        template <typename VST>
        void traverseLevel(VST &visit);
        template <typename VST>
        void traversePre(VST &visit){if(_root){_root->traversePre(visit);}}
        template <typename VST>
        void traversePre_R(BinNodePosi(T)t, VST &visit);
        template <typename VST>
        void traversePre_I1(BinNodePosi(T) tree, VST &visit);

        template <typename VST>
        void traverseIn(VST &visit){if(_root){_root->traverseIn(visit);}}
        template <typename VST>
        void traverseIn_R(BinNodePosi(T) tree, VST &visit);
        template <typename VST>
        void traverseIn_I1(BinNodePosi(T) tree, VST &visit);
        template <typename VST>
        void traverseIn_I2(BinNodePosi(T) tree, VST &visit);
        template <typename VST>
        void traverseIn_I3(BinNodePosi(T) treeNode, VST &visit);


        template <typename VST>
        void traversePost(VST &visit){if(_root){_root->traversePost(visit);}}
        template <typename VST>
        void traversePost_R(BinNodePosi(T) tree, VST &visit);
        template <typename VST>
        void traversePost_I(BinNodePosi(T) tree, VST &visit);

        bool operator<(const BinaryTree<T> &binTree)
        {
            return _root && binTree._root && (*_root < *binTree._root);
        }
        bool operator==(const BinaryTree<T> &binTree)
        {
            return _root && binTree._root && (_root == binTree._root);
        }
    };

    template <typename T>
    BinaryTree<T>::~BinaryTree()
    {
        if(0 < _size)
        {
            remove(_root);
        }
    }

    template <typename T>
    int BinaryTree<T>::updateHeight(BinNodePosi(T) x)
    {
        return x->height = 1 + Max( stature(x->lc) , stature(x->rc));
    }

    template <typename T>
    void BinaryTree<T>::updateHeightAbove(BinNode<T> *x)
    {
        while(x)
        {
            updateHeight(x);
            x = x->parent;
        }
    }

    template <typename T>
    BinNode<T> *BinaryTree<T>::insertAsLeftChild(BinNodePosi(T) x, const T &e)
    {
        ++_size;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }

    template <typename T>
    BinNodePosi(T) BinaryTree<T>::insertAsRightChild(BinNode<T> *x, const T &e)
    {
        ++_size;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }

    template <typename T>
    BinNode<T> *BinaryTree<T>::insertAsRoot(const T &e)
    {
        _size = 1;
        _root = new BinNode<T>(e);
        return _root;
    }

    template <typename T>
    BinNode<T> *BinaryTree<T>::attachAsLeftChild(BinNode<T> *x, BinaryTree<T> *&t)
    {
        if(x->lc = t -> _root)
        {
            x->lc->parent = x;
        }

        _size += t->_size;
        updateHeightAbove(x);

        t->_root = nullptr;
        t->_size = 0;
        delete t;
        t = nullptr;

        return x;
    }

    template <typename T>
    BinNode<T> *BinaryTree<T>::attachAsRightChild(BinNode<T> *x, BinaryTree<T> *&t)
    {
        if(x->rc = t->_root)
        {
            x->rc->parent = t->_root;
        }
        _size += t->size();
        updateHeightAbove(x);

        t->_root = nullptr;
        t->_size = 0;
        release(t);
        t = nullptr;

        return x;
    }

    template <typename T>
    void BinaryTree<T>::release(BinNodePosi(T) x)
    {
        delete x;
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traversePre_R(BinNode<T> *t, VST &visit)
    {
        if(!t)
        {
            return;
        }
        visit(t->data);
        traversePre_R(t->lc, visit);
        traversePre_R(t->rc, visit);
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traverseIn_R(BinNode<T> *tree, VST &visit)
    {
        if(!tree)
        {
            return;
        }
        traverseIn_R(tree->lc, visit);
        visit(tree->data);
        traverseIn_R(tree->rc, visit);
    }

    template <typename T>
    int BinaryTree<T>::remove(BinNode<T> *x)
    {
        FromParentTo(*x) = nullptr;
        updateHeightAbove(x->parent);

        int n = removeAt(x);
        _size -= n;
        return n;

    }

    template <typename T>
    int BinaryTree<T>::removeAt(BinNode<T> *pNode)
    {
        if(!pNode)
        {
            return 0;
        }
        int n = 1 + removeAt(pNode->lc) + removeAt(pNode->rc);

        release(pNode);
        return n;
    }

    //将x从当前的树分离，包装成一个新的树返回
    template <typename T>
    BinaryTree<T> *BinaryTree<T>::secede(BinNode<T> *x)
    {
        FromParentTo(*x) = nullptr;
        updateHeightAbove(x->parent);
        BinaryTree<T> *subTree = new BinaryTree<T>;
        subTree->_root = x;
        x->parent = nullptr;
        subTree->_size = x->size();
        _size -= subTree->_size;
        return subTree;
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traversePost_R(BinNode<T> *tree, VST &visit)
    {
        if(!tree)
        {
            return;
        }

        traversePost_R(tree->lc, visit);
        traversePost_R(tree->rc, visit);
        visit(tree->data);
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traversePre_I1(BinNode<T> *tree, VST &visit)
    {
        sy::Stack<BinNodePosi(T)> traStack;
        while(true)
        {
            visitAlongLeftBranch(tree, visit, traStack);
            if(traStack.empty())
            {
                break;
            }
            tree = traStack.pop();
        }
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::visitAlongLeftBranch(BinNode<T> *tree, VST &visit, sy::Stack<BinNodePosi(T)> &traStack)
    {
        while(tree)
        {
            visit(tree->data);
            traStack.push(tree->rc);
            tree = tree->lc;
        }
    }

    template <typename T>
    void BinaryTree<T>::goAlongLeftBranch(BinNode<T> *tree, sy::Stack<BinNodePosi(T)> &traStack)
    {
        while(tree)
        {
            traStack.push(tree);
            tree = tree->lc;
        }
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traverseIn_I1(BinNode<T> *tree, VST &visit)
    {
        sy::Stack<BinNodePosi(T)> traStack;

        while(true)
        {
            goAlongLeftBranch(tree, traStack);
            if(traStack.empty())
            {
                break;
            }
            tree = traStack.pop();
            visit(tree->data);
            tree = tree->rc;
        }
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traverseIn_I2(BinNode<T> *tree, VST &visit)
    {
        sy::Stack<BinNodePosi(T)> traStack;
        while(true)
        {
            if(tree)
            {
                traStack.push(tree);
                tree = tree->lc;
            }
            else
            {
                if(traStack.empty())
                {
                    break;
                }
                tree = traStack.pop();
                visit(tree->data);
                tree = tree->rc;
            }

        }
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traverseIn_I3(BinNode<T> *treeNode, VST &visit)
    {
        bool backTrack = false;
        while (true)
        {
            if(!backTrack && nullptr != treeNode->lc)
            {
                treeNode = treeNode->lc;
            }
            else
            {
                visit(treeNode->data);
                backTrack = false;
                if(nullptr != treeNode -> rc)
                {
                    treeNode = treeNode->rc;
                }
                else
                {
                    treeNode = treeNode->succ();
                    if(nullptr == treeNode)
                    {
                        break;
                    }
                    backTrack = true;
                }
            }
        }

    }

    template <typename T>
    void BinaryTree<T>::gotoHLVFL(sy::Stack<BinNodePosi(T)> &stack)
    {

        BinNodePosi(T) root = nullptr;
        while(root = stack.top())
        {
            if(HasLChild(*root))
            {
                if(HasRChild(*root))
                {
                    stack.push(root->rc);
                }
                stack.push(root->lc);
            }
            else
            {
                stack.push(root->rc);
            }
        }

        stack.pop();
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traversePost_I(BinNode<T> *tree, VST &visit)
    {
        sy::Stack<BinNodePosi(T)> stack;
        stack.push(tree);
        while(!stack.empty())
        {
            if(tree->parent != stack.top())
            {
                gotoHLVFL(stack);
            }
            tree = stack.pop();
            visit(tree->data);
        }
    }

    template <typename T>
    template <typename VST>
    void BinaryTree<T>::traverseLevel(VST &visit)
    {
        sy::Queue<BinNodePosi(T)> q;
        q.enqueue(root());
        while(!q.empty())
        {
            BinNodePosi(T) x = q.dequeue();
            //visit(x->data);
            std::cout << x->data << " ";
            if(HasLChild(*x))
            {
                q.enqueue(x->lc);
            }
            if(HasRChild(*x))
            {
                q.enqueue(x->rc);
            }
        }
    }
}

#endif //DATASTRUCTS_BINTREE_H

