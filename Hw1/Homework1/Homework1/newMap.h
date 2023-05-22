#ifndef NEWMAP_H
#define NEWMAP_H

#include <string>
#include <iostream>

using namespace std;
using KeyType = std::string;
using ValueType = double;
const int DEFAULT_MAX_ITEMS = 260;


class Map
{
public:
    Map(int val = DEFAULT_MAX_ITEMS);
    Map(const Map& other);
    Map& operator = (const Map& other);
    ~Map();
    bool empty();
    int size();
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key);
    bool get(const KeyType& key, ValueType& value);
    bool get(int i, KeyType& key, ValueType& value);
    void swap(Map& other);
    KeyType getkey(int i);
    ValueType getvalue(int i);
    void dump() const;
private:
    KeyType *m_key;
    ValueType *m_value;
    int m_size;
    int m_maxSize;
};

#endif
