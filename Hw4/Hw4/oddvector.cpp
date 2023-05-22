void removeOdd(vector<int>& v)
{
	for (auto i = v.begin(); i != v.end();)
	{
		if ((*i) % 2 != 0)
		{
			v.erase(i);
			i = v.begin();
		}
		i++;
	}
}