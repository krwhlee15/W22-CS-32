void listAll(string path, const Class* c)  // two-parameter overload
{
    if (c == nullptr)
    {
        return;
    }

    path += c->name();
    cout << path << endl;
    path += "=>";
    for (int i = 0; i < c->subclasses().size(); i++)
    {
        listAll(path, c->subclasses().at(i));
    }
}