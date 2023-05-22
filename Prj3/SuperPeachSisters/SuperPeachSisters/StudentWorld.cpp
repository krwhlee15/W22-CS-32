#include "StudentWorld.h"
#include "Actor.h"
#include "Level.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
	m_peach = nullptr;
	actors.clear();
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}


void StudentWorld::addPiranhaFireball(int x, int y, int dir)
{
	actors.push_back(new PiranhaFireball(this, x, y, dir));
}

void StudentWorld::addPeachFireball(double x, double y, int dir)
{
	actors.push_back(new PeachFireball(this, x, y, dir));
}

void StudentWorld::addShell(int x, int y, int dir)
{
	actors.push_back(new Shell(this, x, y, dir));
}

void StudentWorld::addMushroom(int x, int y)
{
	actors.push_back(new Mushroom(this, x, y));
}

void StudentWorld::addFlower(int x, int y)
{
	actors.push_back(new Flower(this, x, y));
}

void StudentWorld::addStar(int x, int y)
{
	actors.push_back(new Star(this, x, y));
}

bool StudentWorld::overlapping(double x1, double y1, double x2, double y2)
{
	if (x1 + SPRITE_WIDTH > x2 && x1 < x2 + SPRITE_WIDTH)
	{
		if (y1 + SPRITE_HEIGHT > y2 && y1 < y2 + SPRITE_HEIGHT)
		{
			return true;
		}
	}
	return false;
}

bool StudentWorld::overlapping(Actor* a, Actor* b)
{
	return overlapping(a->getX(), a->getY(), b->getX(), b->getY());
}

bool StudentWorld::overlappingPeach(Actor* m)
{
	for (auto a : actors)
	{
		if (a != m)
		{
			if (a->isAlive() && overlapping(m, a))
			{
				return true;
			}
		}
	}
	return false;
}

int StudentWorld::init()
{
	Level lev(assetPath());

	string level_file = "level0" + to_string(getLevel()) + ".txt";
	Level::LoadResult result = lev.loadLevel(level_file);
	if (result == Level::load_fail_file_not_found)
		cerr << "Could not find " << level_file << "data file" << endl;
	else if (result == Level::load_fail_bad_format)
		cerr << level_file << " is improperly formatted" << endl;
	else if (result == Level::load_success)
	{
		cerr << "Successfully loaded level" << endl;
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				Level::GridEntry ge;
				ge = lev.getContentsOf(x, y);
				switch (ge)
				{
				case Level::empty:
					cout << "Location " << x << "," << y << " is empty" << endl;
					break;
				case Level::koopa:
					cout << "Location " << x << "," << y << " starts with a koopa" << endl;
					actors.push_back(new Koopa(this, x, y, 180 * randInt(0,1)));
					break;
				case Level::goomba:
					cout << "Location " << x << "," << y << " starts with a goomba" << endl;
					actors.push_back(new Goomba(this, x, y, 180 * randInt(0, 1)));
					break;
				case Level::piranha:
					cout << "Location " << x << "," << y << " starts with a piranha" << endl;
					actors.push_back(new Piranha(this, x, y, 180 * randInt(0, 1)));
					break;
				case Level::peach:
					cout << "Location " << x << "," << y << " is where Peach starts" << endl;
					m_peach = new Peach(this, x, y);
					break;
				case Level::flag:
					cout << "Location " << x << "," << y << " is where a flag is" << endl;
					actors.push_back(new LevelEnder(this, x, y, IID_FLAG, 0));
					break;
				case Level::mario:
					cout << "Location " << x << "," << y << " is where mario is" << endl;
					actors.push_back(new LevelEnder(this, x, y, IID_MARIO, 1));
					break;
				case Level::pipe:
					cout << "Location " << x << "," << y << " holds a pipe" << endl;
					actors.push_back(new Pipe(this, x, y));
					break;
				case Level::block:
					cout << "Location " << x << "," << y << " holds a regular block" << endl;
					actors.push_back(new Block(this, x, y, 0));
					break;
				case Level::mushroom_goodie_block:
					cout << "Location " << x << "," << y << " has a mushroom goodie block" << endl;
					actors.push_back(new Block(this, x, y, 1));
					break;
				case Level::flower_goodie_block:
					cout << "Location " << x << "," << y << " has a flower goodie block" << endl;
					actors.push_back(new Block(this, x, y, 2));
					break;
				case Level::star_goodie_block:
					cout << "Location " << x << "," << y << " has a star goodie block" << endl;
					actors.push_back(new Block(this, x, y, 3));
					break;
				}
			}
		}
	}
	complete = false;
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	if (m_peach->isAlive())
	{
		m_peach->doSomething();
	}

	vector<Actor*>::iterator it;
	for (it = actors.begin(); it != actors.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->doSomething();
		}
		
		if (!(m_peach->isAlive()))
		{
			decLives();
			cleanUp();
			return GWSTATUS_PLAYER_DIED;
		}

		if (complete)
		{
			return GWSTATUS_FINISHED_LEVEL;
		}

		if (win)
		{
			return GWSTATUS_PLAYER_WON;
		}
	}

	removeDead();

	ostringstream oss;
	oss.setf(ios::fixed);
	oss << "Lives:" << setw(2) << getLives() << setw(9) << "Level: " << setw(2) << setfill('0') << getLevel() << setw(10) << setfill(' ') << "Points: " << setw(6) << setfill('0') << getScore() << setfill(' ');
	if (m_peach->currStarPower())
	{
		oss << " " << "StarPower!";
	}
	if (m_peach->currShootPower())
	{
		oss << " " << "ShootPower!";
	}
	if (m_peach->currJumpPower())
	{
		oss << " " << "JumpPower!";
	}
	setGameStatText(oss.str());

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	delete m_peach;
	vector<Actor*>::iterator it;
	for (it = actors.begin(); it != actors.end(); it++)
	{
		delete* it;
	}
	actors.clear();
	m_peach = nullptr;
}

bool StudentWorld::isValidPos(double x, double y, Actor* me) 
{
	for (auto a : actors)
	{
		if (a != me)
		{
			if (a->isAlive() && a->blocksMove())
			{
				if (overlapping(x, y, a->getX(), a->getY()))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool StudentWorld::isValidPos(double x, double y)
{
	return isValidPos(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, nullptr);
}

void StudentWorld::removeDead()
{
	vector<Actor*>::iterator it;
	for (it = actors.begin(); it != actors.end();)
	{
		if (!((*it)->isAlive()))
		{
			if ((*it)->isKoopa())
			{
				(*it)->whenDead();
			}
			delete (*it);
			it = actors.erase(it);
		}
		else
		{
			it++;
		}
	}
}

Actor* StudentWorld::getOneCollidingEnemy(Actor* a)
{
	vector<Actor*>::iterator it;
	for (it = actors.begin(); it != actors.end(); it++)
	{
		if ((*it)->isEnemy() && overlapping(a, *it))
		{
			return (*it);
		}
	}
	return nullptr;
}

Actor* StudentWorld::getOneCollidingBlock(Actor* a)
{
	vector<Actor*>::iterator it;
	for (it = actors.begin(); it != actors.end(); it++)
	{
		if ((*it)->blocksMove() && overlapping(a, *it))
		{
			return (*it);
		}
	}
	return nullptr;
}

Peach* StudentWorld::getCollidingPeach(Actor* a)
{
	if (overlapping(a, m_peach))
	{
		return m_peach;
	}
	return nullptr;
}