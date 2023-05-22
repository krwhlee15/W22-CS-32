#include "Map.h"
#include <iostream>

Map::Map()
{
    m_size = 0;
}
bool Map::empty()
{
    if (m_size == 0)
    {
        return true;
    }
    return false;
}
int Map::size()
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (this->size() >= DEFAULT_MAX_ITEMS)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < m_size; i++)
        {
            if (m_key[i] == key)
            {
                return false;
            }
        }
        m_key[m_size] = key;
        m_value[m_size] = value;
        m_size++;

        return true;
    }
}
   
bool Map::update(const KeyType& key, const ValueType& value)
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_key[i] == key)
        {
            m_value[i] = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_key[i] == key)
        {
            m_value[i] = value;
            return true;
        }
    }

    if (this->size() >= DEFAULT_MAX_ITEMS)
    {
        return false;
    }
    else
    {
        m_key[m_size] = key;
        m_value[m_size] = value;
        m_size++;
        return true;
    }
}

bool Map::erase(const KeyType& key)
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_key[i] == key)
        {
            for (int j = i; j < m_size; j++)
            {
                m_key[j] = m_key[j + 1];
                m_value[j] = m_value[j + 1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}
bool Map::contains(const KeyType& key)
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_key[i] == key)
        {
            return true;
        }
    }
    return false;
}
    
bool Map::get(const KeyType& key, ValueType& value)
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_key[i] == key)
        {
            value = m_value[i];
            return true;
        }
    }
    return false;
}
bool Map::get(int i, KeyType& key, ValueType& value)
{
    if (i < 0 || i >= m_size)
    {
        return false;
    }
    int count;
    int j;
    if (this->size() == 1)
    {
        key = m_key[0];
        value = m_value[0];
        return true;
    }
    else
    {
        for (j = 0; j < m_size; j++)
        {
            count = 0;
            for (int k = 0; k < m_size; k++)
            {
                if (k == j)
                {
                    k++;
                }
                if (m_key[j] > m_key[k])
                {
                    count++;
                }
            }
            if (count == i)
            {
                key = m_key[j];
                value = m_value[j];
                return true;
            }
        }
    }
    return false;
}
    
void Map::swap(Map& other)
{
    Map temp;

    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        temp.m_key[i] = m_key[i];
        temp.m_value[i] = m_value[i];
    }
    
    temp.m_size = m_size;

    for (int j = 0; j < DEFAULT_MAX_ITEMS; j++)
    {
        m_key[j] = other.m_key[j];
        m_value[j] = other.m_value[j];
    }

    m_size = other.m_size;

    for (int k = 0; k < DEFAULT_MAX_ITEMS; k++)
    {
        other.m_key[k] = temp.m_key[k];
        other.m_value[k] = temp.m_value[k];
    }
    other.m_size = temp.m_size;
}

KeyType Map::getkey(int i)
{
    return m_key[i];
}

ValueType Map::getvalue(int i)
{
    return m_value[i];
}

void Map::dump() const
{
   for (int i = 0; i < m_size; i++)
   {
       cerr << m_key[i] << ", " << m_value[i] << endl;
   }
}