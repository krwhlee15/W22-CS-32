#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* sw, int imageID, double startX, double startY, int startDirection, int depth, double size)
		: GraphObject(imageID, SPRITE_WIDTH * startX, SPRITE_HEIGHT * startY, startDirection, depth, size), m_world(sw), alive(true) {};
	
	virtual void doSomething() = 0;
	
	StudentWorld* getWorld() const { return m_world; };
	
	bool isAlive() { return alive; };
	void setNotAlive() { alive = false; };

	virtual bool isEnemy() { return false; };
	virtual bool isKoopa() { return false; };
	virtual bool blocksMove() { return false; };
	
	virtual void moveTo(double x, double y, Actor* me);
	virtual void whenDead() {};
	virtual void bonked() {};

	bool collidedWithEnemy();
	bool collidedWithBlock();
	bool collidedWithPeach();
private:
	StudentWorld* m_world;
	bool alive;
};

class Peach : public Actor
{
public:
	Peach(StudentWorld* sw, int startX, int startY)
		: Actor(sw, IID_PEACH, startX, startY, 0, 0, 1), m_health(1), starPower(false), shootPower(false), jumpPower(false) {};
	virtual void doSomething();
	virtual void shootFire();
	void jump();
	void bonk(int i);
	void incHealth() { m_health++; if (m_health == 3) { m_health--; } };
	void decHealth() { m_health--; };
	int getHealth() { return m_health; };
	void setStar(bool y) { starPower = y; };
	void setFlower(bool y) { shootPower = y; };
	void setMushroom(bool y) { jumpPower = y; };
	void setStarTick(int st) { star_tick = st; };

	bool currShootPower() { return shootPower; };
	bool currStarPower() { return starPower; };
	bool currJumpPower() { return jumpPower; };
private:
	int m_health;
	int remaining_jump_distance = 0;
	int temp_invincible = 0;
	int fireDelay = 0;
	int star_tick = 0;
	bool starPower, shootPower, jumpPower;
};

///////////////////////////////////////////////////////////////////////////////////
///		Obstacle											///////////////////////
///////////////////////////////////////////////////////////////////////////////////

class Obstacle : public Actor
{
public:
	Obstacle(StudentWorld* sw, int startX, int startY, int imageID)
		: Actor(sw, imageID, startX, startY, 0, 2, 1) {};

	virtual void doSomething() {};
	virtual bool blocksMove() { return true; };
};

class Block : public Obstacle
{
public:
	Block(StudentWorld* sw, int x, int y, int type)
		: Obstacle(sw, x, y, IID_BLOCK), type(type) {};

	virtual void doSomething() {};
	virtual void bonked();
	void setType(int t) { type = t; };
private:
	int type;
};

class Pipe : public Obstacle
{
public:
	Pipe(StudentWorld* sw, int x, int y)
		: Obstacle(sw, x, y, IID_PIPE) {};
	virtual void doSomething() {};
};

///////////////////////////////////////////////////////////////////////////////////
///		LevelEnder											///////////////////////
///////////////////////////////////////////////////////////////////////////////////

class LevelEnder : public Actor
{
public:
	LevelEnder(StudentWorld* sw, int startX, int startY, int imageID, int type)
		: Actor(sw, imageID, startX, startY, 0, 1, 1), type(type) {};
	virtual void doSomething();
private:
	int type;
};

///////////////////////////////////////////////////////////////////////////////////
///		Goodie												///////////////////////
///////////////////////////////////////////////////////////////////////////////////

class Goodie : public Actor
{
public:
	Goodie(StudentWorld* sw, int startX, int startY, int imageID)
		: Actor(sw, imageID, startX, startY, 0, 1, 1) {};
	virtual void doSomething();
};

class Flower : public Goodie
{
public:
	Flower(StudentWorld* sw, int startX, int startY)
		: Goodie(sw, startX, startY, IID_FLOWER) {};
	virtual void doSomething();
};

class Mushroom : public Goodie
{
public:
	Mushroom(StudentWorld* sw, int startX, int startY)
		: Goodie(sw, startX, startY, IID_MUSHROOM) {};
	virtual void doSomething();
};

class Star : public Goodie
{
public:
	Star(StudentWorld* sw, int startX, int startY)
		: Goodie(sw, startX, startY, IID_STAR) {};
	virtual void doSomething();
};

///////////////////////////////////////////////////////////////////////////////////
///		Projectile											///////////////////////
///////////////////////////////////////////////////////////////////////////////////

class Projectile : public Actor
{
public:
	Projectile(StudentWorld* sw, double startX, double startY, int imageID, int startDirection)
		: Actor(sw, imageID, startX, startY, startDirection, 1, 1) {};
	virtual void doSomething();
	
};

class PiranhaFireball : public Projectile
{
public:
	PiranhaFireball(StudentWorld* sw, double startX, double startY, int startDirection)
		: Projectile(sw, startX, startY, IID_PIRANHA_FIRE, startDirection) {};
	virtual void doSomething();
};

class PeachFireball : public Projectile
{
public:
	PeachFireball(StudentWorld* sw, double startX, double startY, int dir)
		: Projectile(sw, startX, startY, IID_PEACH_FIRE, dir) {};
	virtual void doSomething() { Projectile::doSomething(); };
};

class Shell : public Projectile
{
public:
	Shell(StudentWorld* sw, double startX, double startY, int startDirection)
		: Projectile(sw, startX, startY, IID_SHELL, startDirection) {};
	virtual void doSomething() { Projectile::doSomething(); };
};

///////////////////////////////////////////////////////////////////////////////////
///		Enemy												///////////////////////
///////////////////////////////////////////////////////////////////////////////////

class Enemy : public Actor
{
public:
	Enemy(StudentWorld* sw, int startX, int startY, int imageID, int startDirection)
		: Actor(sw, imageID, startX, startY, startDirection, 0, 1) {};
	virtual bool isEnemy() { return true; };
	virtual void doSomething();
};

class Goomba : public Enemy
{
public:
	Goomba(StudentWorld* sw, int startX, int startY, int startDirection)
		: Enemy(sw, startX, startY, IID_GOOMBA, startDirection) {};
	virtual void doSomething() { Enemy::doSomething(); };
};

class Koopa : public Enemy
{
public:
	Koopa(StudentWorld* sw, int startX, int startY, int startDirection)
		: Enemy(sw, startX, startY, IID_KOOPA, startDirection) {};
	virtual void doSomething() { Enemy::doSomething(); };
	virtual bool isKoopa() { return true; };
	void whenDead();
};

class Piranha : public Enemy
{
public:
	Piranha(StudentWorld* sw, int startX, int startY, int startDirection)
		: Enemy(sw, startX, startY, IID_PIRANHA, startDirection) {};
	virtual void doSomething();
	virtual void shootFire();
	bool withinRange(Actor* a);
private:
	int fireDelay = 0;
};

#endif // ACTOR_H_
