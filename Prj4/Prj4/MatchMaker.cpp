#include <map>
#include <set>
#include <algorithm>
#include "MatchMaker.h"

bool operator<(const AttValPair& att1, const AttValPair& att2)
{
    std::string att1Str = att1.attribute + att1.value;
    std::string att2Str = att2.attribute + att2.value;

	if (att1Str < att2Str)
	{
		return true;
	}
    return false;
}

bool operator<(const EmailCount& ec1, const EmailCount& ec2)
{
	if (ec1.count > ec2.count) {
		return true;
	}
	if (ec1.count <= ec2.count) {
		return false;
	}
	return false;
}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
	const PersonProfile* ppTarget = m_mdb->GetMemberByEmail(email);

	std::set<AttValPair> target;
	for (int i = 0; i != ppTarget->GetNumAttValPairs(); i++)
	{
		AttValPair avSource;
		ppTarget->GetAttVal(i, avSource);
		std::vector<AttValPair> cmptPairs = m_at->FindCompatibleAttValPairs(avSource);
		for (auto it = cmptPairs.begin(); it != cmptPairs.end(); it++)
		{
			target.insert(*it);
		}
	}

	std::map<std::string, int> matchCount;
	for (auto it = target.begin(); it != target.end(); it++)
	{
		std::vector<std::string> matchPair = m_mdb->FindMatchingMembers(*it);
		for (auto iit = matchPair.begin(); iit != matchPair.end(); iit++)
		{
			if (*iit != ppTarget->GetEmail())
			{
				matchCount[*iit]++;
			}
		}
	}

	std::vector<EmailCount> rankedMatches;
	for (auto iiit = matchCount.begin(); iiit != matchCount.end(); iiit++)
	{
		if (iiit->second >= threshold) rankedMatches.push_back(EmailCount(iiit->first, iiit->second));
	}

	std::sort(rankedMatches.begin(), rankedMatches.end());

	return rankedMatches;
}