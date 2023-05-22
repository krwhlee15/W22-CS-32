#ifndef RADIXTREE_H
#define RADIXTREE_H

#include <vector>
#include <string>

template <typename ValueType>
class RadixTree {
public:
	RadixTree() { root = nullptr; }
	~RadixTree()
	{
		eraseTree(root);
	}
	void insert(std::string key, const ValueType& value)
	{
		recurInsert(key, value, root);
	}

	ValueType* search(std::string key) const
	{
		return recurSearch(key, root);
	}
private:
	struct Node
	{
	public:
		Node(std::string key, ValueType value)
			:m_key(key), m_value(value), right(nullptr), left(nullptr) {}
		std::string m_key;
		ValueType m_value;
		Node* right;
		Node* left;
	};
	Node* root;
	void eraseTree(Node*& curr)
	{
		if (curr == nullptr)
		{
			return;
		}
		eraseTree(curr->left);
		eraseTree(curr->right);
		delete curr;
	}
	void recurInsert(const std::string& key, const ValueType& value, Node*& curr)
	{
		if (curr == nullptr)
		{
			Node* temp = new Node(key, value);
			curr = temp;
			return;
		}
		else if (curr->m_key == key)
		{
			curr->m_value = value;
			return;
		}
		else if (curr->m_key > key)
		{
			recurInsert(key, value, curr->left);
		}
		else if (curr->m_key < key)
		{
			recurInsert(key, value, curr->right);
		}
	}
	ValueType* recurSearch(std::string& key, Node* curr) const
	{
		if (curr == nullptr)
		{
			return nullptr;
		}
		else if (curr->m_key == key)
		{
			return &(curr->m_value);
		}
		else if (curr->m_key > key)
		{
			return(recurSearch(key, curr->left));
		}
		else
		{
			return(recurSearch(key, curr->right));
		}
	}
};

#endif
