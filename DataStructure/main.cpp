#include "List.h"
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>
#include "BinaryTree.h"
#include <string>
#include "Bitmap.h"
#include <vector>
#include <type_traits>
#include "BST.h"
#include "GraphMatrix.h"
#include "AVL.h"
#include "Splay.h"
#include "BTree.h"
#include "RadBlack.h"
#include "PQ_ComplHeap.h"

#include "String.h"
class Visit
{
public:
    void operator()(int n)
    {
        std::cout << n << " ";
    }
};


int main()
{
	char p[] = {"h"};
	char t[] = { "123abcjjsfas" };
	int m = match(p, t);
	int n = match2(p, t);
	int x = matchKMP("xxx", "wotmdjiucaolehahaha");
	/*sy::BinaryTree<int> biTree;*/
// 	for (int i = 1; i < 10; ++i)
// 	{
// 		std::cout << 4 - (size_t(i) & size_t(3)) << std::endl;
// 	}
// 	sy::List<int> il;
// 	for (int i = 9; i > 0; --i)
// 	{
// 		//il.insertAsFirst(i);
// 		il.insertAsLast(rand() % 10);
// 	}
// 	il.insertAsFirst(1);
// 	il.insertAsFirst(1);
// 	il.insertAsFirst(2);
// 	il.insertAsFirst(2);
// 	il.insertAsLast(99);
// 	il.insertAsLast(99);
// 	int diff = il.deduplicate();
// 	il.traverse(print);
// 	std::cout << std::endl;
// 	il.sort();
// 	il.traverse(print);
	//std::cout << "diff = " << diff << std::endl;
// 	sy::Vector<int> iv;
// 	for (int i = 10; i > 0; --i)
// 	{
// 		iv.insert(rand());
// 	}
// 	iv.traverse([](int i) {std::cout << i << " "; });
// 	std::cout << std::endl;
// 	iv.sort();
// 	iv.traverse([](int i) {std::cout << i << " "; });
// 	sy::Stack<int> is;
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		is.push(i);
// 	}
// 	while (!is.empty())
// 	{
// 		std::cout << is.pop() << " ";
// 		
// 	}
// 	sy::LinkedStack<int> ils;
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		ils.push(i);
// 	}
// 	while (!ils.empty())
// 	{
// 		ils.top();
// 		std::cout << ils.pop() << std::endl;
// 	}
// 	sy::Stack<char> s;
// 	convert(s, 2, 2);
// 	while (!s.empty())
// 	{
// 		std::cout << s.pop();
// 	}
// 	std::cout << std::endl;
// 	char str[] = "(){}[]{()[]}";
// 	std::cout << (paren(str, 0, sizeof(str) - 1) ? "true" : "false") << std::endl;

// 	char s[] = "123*+4-";
// 	//sy::Vector<int> x = {1, 2, 3, 4, 5};
// 	int solu = 0;
// 	int check = 0;
// 	placeQueen(4, solu, check);
// 	placeQueens(4);
	//std::cout << ((nSlolu == solu) ?"true":"false")  << std::endl;

//    sy::Stack<int> s;
//    sy::LinkedStack<int> ls;
//    ls.push(1);
//	sy::Queue<int> q;
//	sy::List<int> l;
//	sy::Vector<int> v;
//    s.push(1);
//	Letter x = A;
//	for (int i = 0; i < 10; ++i)
//	{
//		std::cout << x << std::endl;
//		x = (Letter)(x + 1);
//	}

//     sy::BinaryTree<int> binTree;
// 	binTree.insertAsRoot(1);
// 	BinNodePosi(int) l = binTree.insertAsLeftChild(binTree.root(), 2);
// 	BinNodePosi(int) r = binTree.insertAsRightChild(binTree.root(), 3);
// 	binTree.insertAsRightChild(l, 5);
// 	binTree.insertAsLeftChild(l, 4);
// 
// 	Visit visit;
// 	binTree.traverseLevel(visit);

//   BinNodePosi(int) root = binTree.insertAsRoot(10);
//   for(int i = 0; i < 10; ++i)
//   {
//       if(i & 1)
//       {
//           root = binTree.insertAsLeftChild(root, i);
//           continue;
//       }
//       binTree.insertAsRightChild(root, i);
//   }
   //std::cout << binTree.size() << std::endl;
//    Visit v;
//    binTree.traversePre_R(binTree.root(), v);
//    std::cout << std::endl;
//    binTree.traversePre_I1(binTree.root(), v);
//    std::cout << binTree.size();
//    binTree.traverseIn_R(binTree.root(), v);
//    std::cout << std::endl;
//    binTree.traverseIn_I3(binTree.root(), v);
//    binTree.traversePost_R(binTree.root(), v);
//    std::cout << std::endl;
//    binTree.traversePost_I(binTree.root(), v);
//    binTree.traverseLevel(v);

//     Bitmap bitmap;
//     bitmap.set(0);
//     
//     bitmap.set(2);
//     
//     bitmap.set(4);
// 
//     std::cout << bitmap.bits2string(6);
//    sy::Graph<char, int> *graphMatrix = new sy::GraphMatrix<char, int>();
//	for (char i = 'A'; i < 'I'; ++i)
//	{
//		graphMatrix->insert(i);
//	}
//	graphMatrix->insert(1, 4, 0, 1);
//	graphMatrix->insert(1, 6, 0, 3);
//	graphMatrix->insert(1, 7, 0, 6);
//	graphMatrix->insert(1, 12, 1, 2);
//	graphMatrix->insert(1, 9, 2, 3);
//	graphMatrix->insert(1, 1, 2, 4);
//	graphMatrix->insert(1, 2, 2, 5);
//	graphMatrix->insert(1, 10, 2, 7);
//	graphMatrix->insert(1, 13, 3, 4);
//	graphMatrix->insert(1, 2, 3, 6);
//	graphMatrix->insert(1, 5, 4, 5);
//	graphMatrix->insert(1, 8, 4, 7);
//	graphMatrix->insert(1, 11, 4, 6);
//	graphMatrix->insert(1, 7, 5, 7);
//	graphMatrix->insert(1, 14, 6, 7);
//
//	graphMatrix->prim(0);
//     for(int i = 0; i < 10; ++i)
//     {
//         graphMatrix->insert(i);
//     }

//    graphMatrix->insert(100, 1, 1, 5);
//    graphMatrix->insert(100, 1, 1, 8);
//    graphMatrix->insert(100, 1, 1, 9);
//     graphMatrix->insert(100, 1, 1, 3);
//     //graphMatrix->bfs(0);
//     graphMatrix->insert(100, 1, 3, 2);
//     graphMatrix->insert(100, 1, 2, 6);
//     graphMatrix->dfs(0);

//	sy::BST<int> bst;
//	bst.insert(1);
//	bst.insert(2);
//	bst.insert(3);
//	bst.insert(4);
//	bst.insert(5);
//
//	Visit v;
//	bst.traverseLevel(v);
//
//	std::cout << bst.maxDepth(bst.root());
//
//	std::cout << "wocao" << std::endl;
//	Visit visit;
//	bst.traverseLevel(visit);
//
//	bst.remove(3);
//	std::cout << std::endl;
//
//	bst.traverseLevel(visit);
//	sy::AVL<int> avl;
//	avl.insert(3);
//	avl.insert(2);
//	avl.insert(1);
//	avl.insert(7);
//	avl.insert(6);
//	avl.insert(4);
//	avl.insert(5);
//	avl.insert(8);

// 	sy::Splay<int> splay;
// 
// 	splay.insert(1);
// 	splay.insert(3);
// 	splay.insert(4);
// 	splay.insert(8);
// 	splay.insert(5);
// 	splay.insert(6);
// 	splay.insert(7);
// 	
// 	splay.traverseLevel(visit);
// 
// 	std::cout << std::endl;
// 	splay.remove(7);
// 	splay.traverseLevel(visit);

//	sy::BTree<int> bTree(6);
//	bTree.insert(17);
//	bTree.insert(20);
//	bTree.insert(31);
//	bTree.insert(37);
//	bTree.insert(41);
//	bTree.insert(56);
//	bTree.insert(51);
//	bTree.insert(75);
//	bTree.insert(79);
//	bTree.insert(84);
//	bTree.insert(97);

// 	sy::RedBlcak<int> redBlack;
// 	redBlack.insert(1);
// 	redBlack.insert(2);
// 	redBlack.remove(2);
// 	Visit visit;
// 	redBlack.traverseLevel(visit);
// 	system("pause");

sy::PQ_ComplHeap<int> priorityHeap;

priorityHeap.insert(1);
priorityHeap.insert(2);
priorityHeap.insert(3);


}