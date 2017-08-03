//
// Created by magicsun on 16-3-5.
//

#ifndef DATASTRUCTURE_ENTRY_H
#define DATASTRUCTURE_ENTRY_H
template <typename K, typename V>
struct Entry
{

    K key;
    V value;
    Entry(const K &key_ = K(), const V &value_ = V()):key(key_), value(value_){}
    bool operator< (const Entry<K, V>&rhs) { return this->key < rhs.key; }
    bool operator> (const Entry<K, V>&rhs) { return this->key > rhs.key; }
    bool operator== (const Entry<K, V>&rhs) { return  this->key == rhs.key; }
    bool operator!= (const Entry<K, V>&rhs) { return !(*this == rhs); }

};
#endif //DATASTRUCTURE_ENTRY_H
