#include "CarMap.h"

CarMap::CarMap():m_map()
{

}

bool CarMap::addCar(std::string license)
{
	return m_map.insert(license, 0);
}

double CarMap::miles(std::string license)
{
	ValueType mi = -1;
	KeyType key = license;
	m_map.get(key, mi);
	return mi;
}

bool CarMap::drive(std::string license, double distance)
{
	double mi = -1;
	if (!m_map.get(license, mi))
	{
		return false;
	}
	return m_map.update(license, mi + distance);
}

int CarMap::fleetSize()
{
	int fleetSize = m_map.size();
	return fleetSize;
}

void CarMap::print()
{
	for (int i = 0; i < m_map.size(); i++)
	{
		cerr << m_map.getkey(i) << " " << m_map.getvalue(i) << endl;
	}
}