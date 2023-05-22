#include "PersonProfile.h"
#include "provided.h"

PersonProfile::~PersonProfile()
{
	for (auto it = m_attval.begin(); it != m_attval.end(); it++)
	{
		delete m_avTree->search((*it)->value);
		delete (*it);
	}
	delete m_avTree;
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
	std::set<std::string> empty = {};
	std::set<std::string>* found = m_avTree->search(attval.attribute);

	if (found == nullptr) 
	{
		m_avTree->insert(attval.attribute, empty);
		found = m_avTree->search(attval.attribute);
	}

	if (found->find(attval.value) == found->end())
	{
		std::set<std::string>* temp = new std::set<std::string>(*found);
		temp->insert(attval.value);

		m_avTree->insert(attval.attribute, *temp);

		m_attval.push_back(new AttValPair(attval));
		delete temp;
	}
	
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	if (attribute_num < 0 || attribute_num >= GetNumAttValPairs())
	{
		return false;
	}
	attval = *m_attval[attribute_num];
	return true;
}