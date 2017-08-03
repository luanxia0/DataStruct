cmake_minimum_required(VERSION 2.8.4)
project(DataStructure)

set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BinaryTree.h BinaryTreeNode.h Bitmap.h
                 Bitmap.cpp Graph.h GraphMatrix.h List.h ListNode.h
                 Queue.h Stack.h Utility.h Vector.h Entry.h BST.h AVL.h Splay.h BTNode.h BTree.h RadBlack.h)
add_executable(DataStructure ${SOURCE_FILES})