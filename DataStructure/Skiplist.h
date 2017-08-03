#pragma once
#include "List.h"
#include "Entry.h"
#include "Dictionary.h"
#include "Quadlist.h"

template<typename K, typename V>
class Skiplist : public Dictionarty<K, V>, public List<Quadlist<Entry<K, V>>*>
{
protected:
	bool skipSearch(ListNode<Quadlist<Entry<K, V>>*> *&qlist, QuadlistNode<Entry<K, V>> *&p, const K& k);
public:
	virtual int size() const {return empty() ? 0 : last()->data->size()};
	int level() { return List::size(); };
	bool put(const K &key, const V &value);
	V* get(const K &key);
	bool remove(const K &key);
};

template<typename K, typename V>
inline bool Skiplist<K, V>::skipSearch(ListNode<Quadlist<Entry<K, V>>*>*& qlist, QuadlistNode<Entry<K, V>>*& p, const K & k)
{
	while (true)
	{
		while (p->succ && (p->entry.key <= k))
		{
			p = p->succ;
		}
		p = p->pred;
		if (p->pred && (k == p->entry.key))
		{
			return true;
		}

		qlist = qlist->succ;
		if (!qlist->succ)
		{
			return false;
		}

		p = (p->pred) ? p->below : qlist->data->first();
	}
}

template<typename K, typename V>
inline V * Skiplist<K, V>::get(const K & key)
{
	if(empty())
	{
		return nullptr;
	}

	sy::ListNode<Quadlist<Entry<K, V>>*> * qlist = first();
	QuadlistNode<Entry<K, V>>* p = qlist->data->first();

	return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr;
}
