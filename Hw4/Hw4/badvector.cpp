void removeBad(vector<Movie*>& v)
{
    for (auto i = v.begin(); i != v.end(); i++)
    {
        if ((*i)->rating() < 50)
        {
            delete* i;
            i = v.erase(i);
            i--;
        }
    }
}
