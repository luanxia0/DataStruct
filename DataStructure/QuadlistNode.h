#pragma once
#include "Entry.h"


#define  QlistNodePosi(T) QuadlistNode<T>*

template<typename T>
class QuadlistNode
{
public:
	T entry;
	QlistNodePosi(T) pred;
	QlistNodePosi(T) succ;
	QlistNodePosi(T) above;
	QlistNodePosi(T) below;

	QuadlistNode(const T &e, QlistNodePosi(T) p = nullptr, QlistNodePosi(T) s = nullptr, QlistNodePosi(T) a = nullptr, QlistNodePosi(T) b = nullptr)
		:entry(e), pred(p), succ(s), above(a), below(b){}

	QlistNodePosi(T) insertAsSuccAbove(const T &e, QlistNodePosi(T) b = nullptr);
};
