#ifndef MEMBERDATABASE_H
#define MEMBERDATABASE_H

#include <vector>
#include <set>
#include "PersonProfile.h"
#include "RadixTree.h"

struct AttValPair;

class MemberDatabase {
public:
	MemberDatabase()
		: m_etopTree(new RadixTree<PersonProfile*>), m_avtoeTree(new RadixTree<std::vector<std::string>*>),
		m_email(new std::set<std::string>), m_av(new std::set<std::string>) {}
	~MemberDatabase();
	bool LoadDatabase(std::string filename);
	std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(std::string email) const;
private:
	RadixTree<PersonProfile*>* m_etopTree;
	RadixTree<std::vector<std::string>*>* m_avtoeTree;
	std::set<std::string>* m_email;
	std::set<std::string>* m_av;
};

#endif
