void removeOdd(list<int>& li)
{
	for (auto i = li.begin(); i != li.end();)
	{
		if ((*i) % 2 != 0)
		{
			li.erase(i);
			i = li.begin();
		}
		i++;
	}
}