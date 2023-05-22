#include <fstream>
#include <iostream>
#include "MemberDatabase.h"
#include "provided.h"

MemberDatabase::~MemberDatabase()
{
	for (auto it = m_email->begin(); it != m_email->end(); it++)
	{
		delete (*m_etopTree->search(*it));
	}
	
	for (auto it = m_av->begin(); it != m_av->end(); it++)
	{
		delete (*m_avtoeTree->search(*it));
	}
	
	delete m_etopTree;
	delete m_avtoeTree;
	delete m_email;
	delete m_av;
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
	std::ifstream dbFile(filename);
	if (dbFile.fail()) {
		return false;
	}
	else
	{
		std::string name;
		std::string email;
		int count = 0;
		std::string att;
		std::string val;

		std::string ignore;
		
		while (dbFile.good())
		{
			std::getline(dbFile, name);
			std::getline(dbFile, email);
			
			if (m_etopTree->search(email) != nullptr)
			{
				return false;
			}
			
			m_email->insert(email);
			PersonProfile* newpp = new PersonProfile(name, email);

			
			dbFile >> count;
			std::getline(dbFile, ignore);
			
			for (int i = 0; i != count; i++)
			{
				std::getline(dbFile, att, ',');
				std::getline(dbFile, val);
				newpp->AddAttValPair(AttValPair(att, val));

				std::string key = att + val;
				std::vector<std::string>** emailVec = m_avtoeTree->search(key);
		
				if (emailVec == nullptr) {
					m_avtoeTree->insert(key, new std::vector<std::string>);
					emailVec = m_avtoeTree->search(key);
					m_av->insert(key);
				}
				(*emailVec)->push_back(email);
			}
			std::getline(dbFile, ignore);
			m_etopTree->insert(email, newpp);
		}
	}
	return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	std::vector<std::string>** matchingMembers = m_avtoeTree->search(input.attribute + input.value);
	if (matchingMembers != nullptr)
	{
		return **m_avtoeTree->search(input.attribute + input.value);
	}
	return std::vector<std::string>();
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	PersonProfile** pp = m_etopTree->search(email);
	if (pp != nullptr)
	{
		return *pp;
	}
	return nullptr;
}
