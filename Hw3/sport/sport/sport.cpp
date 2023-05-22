#include <iostream>
#include <string>
using namespace std;

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

void display(const Sport* sp)
{
    cout << sp->name() << " is ";
    if (sp->isOutdoor())
        cout << "an outdoor sport ";
    else
        cout << "an indoor sport ";
    cout << "with an icon showing " << sp->icon() << "." << endl;
}

int main()
{
    Sport* sports[4];
    sports[0] = new Snowboarding("Women's halfpipe");
    // Biathlon events have a distance in kilometers
    sports[1] = new Biathlon("Men's pursuit", 12.5);
    sports[2] = new Biathlon("Women's sprint", 7.5);
    sports[3] = new FigureSkating("Pair skating free");

    cout << "Here are the sports." << endl;
    for (int k = 0; k < 4; k++)
        display(sports[k]);

    // Clean up the sports before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete sports[k];
}