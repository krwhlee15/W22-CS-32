#include "Map.h"
#include <iostream>

using namespace std;

Map::Map()
{
    head = new Node;
    head->next = head;
    head->prev = head;
    m_size = 0;
}

Map::Map(const Map& other)
{
    head = new Node;
    head->next = head;
    head->prev = head;
    this->m_size = 0;

    for (Node* temp = other.head->next; temp != other.head; temp = temp->next)
    {
        this->insert(temp->keyData, temp->valueData);
    }
}

Map& Map::operator=(const Map& other)
{
    if (this != &other)
    {
        Map temp(other);
        swap(temp);
    }
    return *this;
}

Map::~Map()
{
    while (head != head->next)
    {
        Node* del = head->next;
        head->next = del->next;
        del->next->prev = head;
        delete del;
    }
    delete head;
}

bool Map::empty() const
{
    return (m_size == 0);
}

int Map::size() const
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{   
    Node* m;
    for (m = head->next; m != head; m = m->next)
    {
        if (m->keyData == key)
        {
            return false;
        }
    }

    if (m_size == 0)
    {
        head->next = new Node;
        head->next->keyData = key;
        head->next->valueData = value;
        head->next->next = head;
        head->next->prev = head;
    }
    else
    {
        Node* m;
        for (m = head->next; m->next != head && key > m->keyData; m = m->next)
        {
        }
        if (m->next == head && key > m->keyData)	
        {
            Node* newNode = new Node;
            newNode->keyData = key;
            newNode->valueData = value;
            newNode->next = m->next;
            m->next = newNode;
            newNode->prev = m;
        }
        else
        {
            Node* newNode = new Node;
            newNode->keyData = key;
            newNode->valueData = value;
            newNode->next = m;
            newNode->prev = m->prev;
            m->prev->next = newNode;
            m->prev = newNode;
        }
    }
    m_size++;
    return true;
}
   
bool Map::update(const KeyType& key, const ValueType& value)
{
    for (Node* m = head->next; m != head; m = m->next)
    {
        if (m->keyData == key)
        {
            m->valueData = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (insert(key, value))
    {
        return true;
    }
    return(update(key, value));
}

bool Map::erase(const KeyType& key)
{
    bool erased = false;
    for (Node* m = head->next; m != head; m = m->next)
    {
        if (m->keyData == key)
        {
            Node* temp = m;
            m = m->prev;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            m_size--;
            erased = true;
        }
    }
    return erased;
}
bool Map::contains(const KeyType& key) const
{
    for (Node* m = head->next; m != head; m = m->next)
    {
        if (m->keyData == key)
        {
            return true;
        }
    }
    return false;
}
    
bool Map::get(const KeyType& key, ValueType& value) const
{
    for (Node* m = head->next; m != head; m = m->next)
    {
        if (m->keyData == key)
        {
            value = m->valueData;
            return true;
        }
    }
    return false;
}
bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0 || i >= m_size)
    {
        return false;
    }
    else
    {
        Node* m;
        int count = 0;
        for (m = head->next; count < i; m = m->next)
        {
            count++;
        }

        key = m->keyData;
        value = m->valueData;
        return true;
    }
}
    
void Map::swap(Map& other)
{
    Node* m = head;
    int s = m_size;

    head = other.head;
    m_size = other.m_size;

    other.head = m;
    other.m_size = s;
}

bool merge(const Map& m1, const Map& m2, Map& result)
{
    if (m1.empty())
    {
        result = m2;
        return true;
    }
    else if (m2.empty())
    {
        result = m1;
        return true;
    }
    
    int size = (m1.size() >= m2.size()) ? m1.size() : m2.size();
    Map temp1 = m1;
    Map temp2 = m2;
    KeyType tempKey, temp1Key, temp2Key;
    ValueType tempValue, temp1Value, temp2Value;
    bool notErased = true;

    for (int i = 0; i < m1.size(); i++)
    {
        temp1.get(i, temp1Key, temp1Value);
        for (int j = 0; j < m2.size(); j++)
        {
            temp2.get(j, temp2Key, temp2Value);
            if (temp1Key == temp2Key && temp1Value != temp2Value)
            {
                temp1.erase(temp1Key);
                temp2.erase(temp2Key);
                notErased = false;
                i--;
            }
        }
    }

    for (int k = 0; k < size; k++)
    {
        if (temp1.get(k, tempKey, tempValue))
        {
            result.insert(tempKey, tempValue);
        }
        if (temp2.get(k, tempKey, tempValue))
        {
            result.insert(tempKey, tempValue);
        }
    }

    return notErased;
}

void reassign(const Map& m, Map& result)
{
    ValueType* tempValue = new ValueType[m.size()];
    KeyType* tempKey = new KeyType[m.size()];

    for (int i = 0; i < m.size(); i++)
    {
        m.get(i, tempKey[i], tempValue[i]);
    }

    for (int j = 0; j < m.size() - 1; j++)
    {
        result.insert(tempKey[j], tempValue[j+1]);
    }
    result.insert(tempKey[m.size() - 1], tempValue[0]);

    delete[] tempValue;
    delete[] tempKey;
}

void Map::dump() const
{
    for (Node* m = head->next; m != head; m = m->next)
    {
        cerr << m->keyData << ", " << m->valueData << endl;
    }
    cout << endl;
}
