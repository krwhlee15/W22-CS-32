#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	bool isValidPos(double x, double y, Actor* me);
	bool isValidPos(double x, double y);

	void addPiranhaFireball(int x, int y, int dir);
	void addPeachFireball(double x, double y, int dir);
	void addShell(int x, int y, int dir);
	void addMushroom(int x, int y);
	void addFlower(int x, int y);
	void addStar(int x, int y);
	
	void removeDead();

	bool overlapping(double x1, double y1, double x2, double y2);
	bool overlapping(Actor* a, Actor* b);
	bool overlappingPeach(Actor* m);

	void levelComplete() { complete = true; };
	void gameWon() { win = true; };

	Actor* getOneCollidingEnemy(Actor* a);
	Actor* getOneCollidingBlock(Actor* a);
	Peach* getCollidingPeach(Actor* a);
	Peach* getPeach() { return m_peach; };
private:
	bool complete;
	bool win = false;

	Peach* m_peach;
	std::vector<Actor*> actors;
};

#endif // STUDENTWORLD_H_
