class Sport
{
public:
    Sport(string sp) : s_name(sp) {};
    virtual ~Sport() {};
    string name() const { return s_name; };
    virtual int isOutdoor() const = 0;
    virtual string icon() const = 0;
private:
    string s_name;
};

class Snowboarding : public Sport
{
public:
    Snowboarding(string sp) : Sport(sp) {};
    virtual ~Snowboarding()
    {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    };
    virtual int isOutdoor() const { return 1; };
    virtual string icon() const { return "a descending snowboarder"; };
};

class Biathlon : public Sport
{
public:
    Biathlon(string sp, double dist) : Sport(sp), s_dist(dist) {};
    virtual ~Biathlon()
    {
        cout << "Destroying the Biathlon object named " << name() << ", distance " << s_dist << " km." << endl;
    };
    virtual int isOutdoor() const { return 1; };
    virtual string icon() const { return "a skier with a rifle"; };
private:
    double s_dist;
};

class FigureSkating : public Sport
{
public:
    FigureSkating(string sp) : Sport(sp) {};
    virtual ~FigureSkating()
    {
        cout << "Destroying the FigureSkating object named " << name() << "." << endl;
    };
    virtual int isOutdoor() const { return 0; };
    virtual string icon() const { return "a skater in the Biellmann position"; };
};
