void removeBad(list<Movie*>& li)
{
    for (auto i = li.begin(); i != li.end(); i++)
    {
        if ((*i)->rating() < 50)
        {
            delete* i;
            i = li.erase(i);
            i--;
        }
    }
}