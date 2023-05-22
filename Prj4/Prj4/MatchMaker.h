#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker {
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
		: m_mdb(&mdb), m_at(&at) {};
	~MatchMaker() {};
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
	const MemberDatabase* m_mdb;
	const AttributeTranslator* m_at;
};

#endif