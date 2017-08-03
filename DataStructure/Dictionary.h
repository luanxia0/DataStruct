#pragma once
template<typename K, typename V>
struct Dictionarty
{
	virtual int size() const = 0;
	virtual bool put(const K &, const V &) = 0;
	virtual V* get(const K &k) = 0;
	virtual bool remove(const K &k) = 0;
};
