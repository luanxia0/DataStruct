#pragma once
#include "QuadlistNode.h"

template<typename T>
class Quadlist
{
private:
	int _size;
	QlistNodePosi(T) header;
	QlistNodePosi(T) trailer;

protected:
	void init();
	int clear();

public:
	Quadlist() { init(); }
	~Quadlist() { clear(); delete header; delete trailer; }

	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	QlistNodePosi(T) first() const { return header->succ; }
	QlistNodePosi(T) last() const { return trailer->pred; }
	bool valid(QlistNodePosi(T) p) { return !p && p != header && p != trailer; }

	T remove(QlistNodePosi(T) p);
	QlistNodePosi(T) insertAfterAbove(const T &e, QlistNodePosi(T) p, QlistNodePosi(T) b = nullptr);
	void traverse(void(*v)(T &e));
	template<typename VST>
	void traverse(const VST& v);
};

template<typename T>
inline void Quadlist<T>::init()
{
	header = new QuadlistNode<T>();
	trailer = new QuadlistNode<T>();

	header->succ = trailer;
	header->pred = nullptr;

	trailer->pred = header;
	trailer->succ = nullptr;

	header->above = trailer->above = nullptr;
	header->below = trailer->below = nullptr;

	_size = 0;
}
