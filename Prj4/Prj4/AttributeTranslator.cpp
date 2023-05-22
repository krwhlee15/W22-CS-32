#include <fstream>
#include <iostream>
#include "AttributeTranslator.h"

AttributeTranslator::~AttributeTranslator()
{
	for (auto it = m_source->begin(); it != m_source->end(); it++)
	{
		delete (*m_ptopTree->search(*it));
	}
	delete m_ptopTree;
	delete m_source;
}

bool AttributeTranslator::Load(std::string filename)
{
	std::ifstream tfile(filename);
	if (tfile.fail())
	{
		return false;
	}
	else
	{
		while (tfile.good())
		{
			std::string sourceAtt;
			std::string sourceVal;
			std::string cmptAtt;
			std::string cmptVal;

			std::getline(tfile, sourceAtt, ',');
			std::getline(tfile, sourceVal, ',');
			std::getline(tfile, cmptAtt, ',');
			std::getline(tfile, cmptVal);
			
			std::string key(sourceAtt + sourceVal);
			AttValPair cmpt(cmptAtt, cmptVal);

			std::vector<AttValPair>** cmptVec = m_ptopTree->search(key);
			
			if (cmptVec == nullptr)
			{
				m_ptopTree->insert(key, new std::vector<AttValPair>);
				cmptVec = m_ptopTree->search(key);
				m_source->insert(key);
			}
			(*cmptVec)->push_back(cmpt);
		}
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	std::vector<AttValPair> empty = {};
	std::vector<AttValPair>** vec = m_ptopTree->search(source.attribute + source.value);
	if (vec != nullptr)
	{
		return **vec;
	}
	return empty;
}

