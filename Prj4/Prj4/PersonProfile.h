#ifndef PERSONPROFILE_H
#define PERSONPROFILE_H

#include <string>
#include <vector>
#include <set>
#include "RadixTree.h"

struct AttValPair;

class PersonProfile {
public:
	PersonProfile(std::string name, std::string email)
		: m_name(name), m_email(email), m_avTree(new RadixTree<std::set<std::string>>), m_attval(std::vector<AttValPair*>()) {}
	~PersonProfile();
	std::string GetName() const { return m_name; }
	std::string GetEmail() const { return m_email; }
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const { return m_attval.size(); }
	bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
	std::string m_name;
	std::string m_email;
	RadixTree<std::set<std::string>>* m_avTree;
	std::vector<AttValPair*> m_attval;
};

#endif
