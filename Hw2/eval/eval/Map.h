#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>

using namespace std;
using KeyType = char;
using ValueType = int;
const int DEFAULT_MAX_ITEMS = 260;


class Map
{
public:
    Map();
    Map(const Map& other);
    Map& operator=(const Map& other);
    ~Map();
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const;
private:
    struct Node
    {
        KeyType keyData;
        ValueType valueData;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    int m_size;
};

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif
