#ifndef ATTRIBUTETRANSLATOR_H
#define ATTRIBUTETRANSLATOR_H

#include <vector>
#include <set>
#include <string>
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator {
public:
	AttributeTranslator()
		: m_ptopTree(new RadixTree<std::vector<AttValPair>*>), m_source(new std::set<std::string>) {}
	~AttributeTranslator();
	bool Load(std::string filename);
	std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
	RadixTree<std::vector<AttValPair>*>* m_ptopTree;
	std::set<std::string>* m_source;
};

#endif
