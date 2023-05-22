#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

///////////////////////////////////////////////////////////////////////////////////
///		Actor												///////////////////////
///////////////////////////////////////////////////////////////////////////////////

void Actor::moveTo(double x, double y, Actor* me)
{
	if (getWorld()->isValidPos(x, y, me))
	{
		GraphObject::moveTo(x, y);
	}
}

bool Actor::collidedWithBlock()
{
	Actor* a = dynamic_cast<Actor*>(getWorld()->getOneCollidingBlock(this));
	if (a != nullptr)
	{
		return true;
	}
	return false;
}

bool Actor::collidedWithEnemy()
{
	Actor* a = dynamic_cast<Actor*>(getWorld()->getOneCollidingEnemy(this));
	if (a != nullptr)
	{
		return true;
	}
	return false;
}

bool Actor::collidedWithPeach()
{
	Actor* a = dynamic_cast<Actor*>(getWorld()->getCollidingPeach(this));
	if (a != nullptr)
	{
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////
///		Peach												///////////////////////
///////////////////////////////////////////////////////////////////////////////////

void Peach::doSomething()
{
	int ch;
	if (remaining_jump_distance == 0)
	{
		moveTo(getX(), getY() - 4, this);
	}
	jump();

	if (temp_invincible > 0)
	{
		temp_invincible--;
	}

	if (star_tick > 0)
	{
		star_tick--;
	}

	if (star_tick == 0)
	{
		setStar(false);
	}

	if (fireDelay > 0)
	{
		fireDelay--;
	}

	if (getWorld()->getKey(ch))
	{
		// user hit a key during this tick!
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(left);
			bonk(1);
			moveTo(getX() - 4, getY(), this);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			bonk(0);
			moveTo(getX() + 4, getY(), this);
			break;
		case KEY_PRESS_UP:
			if (!getWorld()->isValidPos(getX(), getY() - 1, this))
			{
				getWorld()->playSound(SOUND_PLAYER_JUMP);
				if (remaining_jump_distance == 0)
				{
					remaining_jump_distance = (jumpPower) ? 12 : 8;
				}
			}
			//moveTo(getX(), getY() + 8, this);
			break;
		case KEY_PRESS_DOWN:
			moveTo(getX(), getY() - 8, this);
			break;
		case KEY_PRESS_SPACE:
			if (shootPower)
			{
				shootFire();
			}
			break;
		}
	}

	if (collidedWithEnemy())
	{
		if (starPower)
		{
			getWorld()->increaseScore(100);
			getWorld()->playSound(SOUND_PLAYER_KICK);
			getWorld()->getOneCollidingEnemy(this)->setNotAlive();
		}
		else if (temp_invincible == 0)
		{
			decHealth();
			shootPower = false;
			jumpPower = false;
			if (m_health == 0)
			{
				setNotAlive();
				getWorld()->playSound(SOUND_PLAYER_DIE);
			}
			else
			{
				getWorld()->playSound(SOUND_PLAYER_HURT);
				temp_invincible = 10;
			}
		}
	}
	return;
}

void Peach::bonk(int i)
{
	switch (i)
	{
	case 0:
		if (!getWorld()->isValidPos(getX() + 1, getY(), this))
		{
			GraphObject::moveTo(getX() + 1, getY());
			getWorld()->getOneCollidingBlock(this)->bonked();
			GraphObject::moveTo(getX() - 1, getY());
			getWorld()->playSound(SOUND_PLAYER_BONK);
		}
		break;
	case 1:
		if (!getWorld()->isValidPos(getX() - 1, getY(), this))
		{
			GraphObject::moveTo(getX() - 1, getY());
			getWorld()->getOneCollidingBlock(this)->bonked();
			GraphObject::moveTo(getX() + 1, getY());
			getWorld()->playSound(SOUND_PLAYER_BONK);
		}
		break;
	case 2:
		if (!getWorld()->isValidPos(getX(), getY() + 1, this))
		{
			GraphObject::moveTo(getX(), getY() + 1);
			getWorld()->getOneCollidingBlock(this)->bonked();
			GraphObject::moveTo(getX(), getY() - 1);
			getWorld()->playSound(SOUND_PLAYER_BONK);
			remaining_jump_distance = 0;
		}
		break;
	}

}

void Peach::jump()
{
	if (remaining_jump_distance > 0)
	{
		moveTo(getX(), getY() + 4, this);
		remaining_jump_distance--;
	}
	bonk(2);
}

void Peach::shootFire()
{
	if (fireDelay > 0)
	{
		fireDelay--;
		return;
	}

	getWorld()->playSound(SOUND_PLAYER_FIRE);

	int dir = getDirection();
	double px = getX();
	double py = getY();
	switch (dir)
	{
	case left:
		getWorld()->addPeachFireball((px - 4) / SPRITE_WIDTH, py / SPRITE_HEIGHT, dir);
		break;
	case right:
		getWorld()->addPeachFireball((px + 4) / SPRITE_WIDTH, py / SPRITE_HEIGHT, dir);
		break;
	}

	fireDelay = 8;
}

///////////////////////////////////////////////////////////////////////////////////
///		Block												///////////////////////
///////////////////////////////////////////////////////////////////////////////////

void Block::bonked()
{
	switch (type)
	{
	case 1:
		getWorld()->addMushroom(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT + 1);
		getWorld()->playSound(SOUND_POWERUP_APPEARS);
		break;
	case 2:
		getWorld()->addFlower(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT + 1);
		getWorld()->playSound(SOUND_POWERUP_APPEARS);
		break;
	case 3:
		getWorld()->addStar(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT + 1);
		getWorld()->playSound(SOUND_POWERUP_APPEARS);
		break;
	default:
		break;
	}
	setType(0);
}

///////////////////////////////////////////////////////////////////////////////////
///		LevelEnder											///////////////////////
///////////////////////////////////////////////////////////////////////////////////

void LevelEnder::doSomething()
{
	if (collidedWithPeach())
	{
		getWorld()->increaseScore(1000);
		switch (type)
		{
		case 0:
			getWorld()->playSound(SOUND_FINISHED_LEVEL);
			getWorld()->levelComplete();
			break;
		case 1:
			getWorld()->playSound(SOUND_GAME_OVER);
			getWorld()->gameWon();
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////
///		Goodie												///////////////////////
///////////////////////////////////////////////////////////////////////////////////

void Goodie::doSomething()
{
	int dir = getDirection();
	double px = getX();
	double py = getY();

	switch (dir)
	{
	case left:
		if (!getWorld()->isValidPos(px - 2, py, this))
		{
			setDirection(right);
		}
		break;
	case right:
		if (!getWorld()->isValidPos(px + 2, py, this))
		{
			setDirection(left);
		}
		break;
	}
	switch (dir)
	{
	case left:
		moveTo(px - 2, py, this);
		break;
	case right:
		moveTo(px + 2, py, this);
		break;
	}

	moveTo(getX(), getY() - 2, this);
}

void Star::doSomething()
{
	Goodie::doSomething();
	if (collidedWithPeach())
	{
		getWorld()->getPeach()->setStar(true);
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		getWorld()->increaseScore(100);
		getWorld()->getPeach()->setStarTick(150);
		setNotAlive();
	}
}

void Flower::doSomething()
{
	Goodie::doSomething();
	if (collidedWithPeach())
	{
		getWorld()->getPeach()->setFlower(true);
		getWorld()->getPeach()->incHealth();
		getWorld()->increaseScore(50);
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		setNotAlive();
	}
}

void Mushroom::doSomething()
{
	Goodie::doSomething();
	if (collidedWithPeach())
	{
		getWorld()->getPeach()->setMushroom(true);
		getWorld()->getPeach()->incHealth();
		getWorld()->increaseScore(75);
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		setNotAlive();
	}
}

///////////////////////////////////////////////////////////////////////////////////
///		Projectile											///////////////////////
///////////////////////////////////////////////////////////////////////////////////

void Projectile::doSomething()
{
	int dir = getDirection();
	double px = getX();
	double py = getY();

	if (isAlive())
	{
		if (collidedWithEnemy() || collidedWithBlock())
		{
			if (collidedWithEnemy())
			{
				getWorld()->increaseScore(100);
				getWorld()->getOneCollidingEnemy(this)->setNotAlive();
			}
			setNotAlive();
			return;
		}

		switch (dir)
		{
		case left:
			GraphObject::moveTo(px - 2, py);
			break;
		case right:
			GraphObject::moveTo(px + 2, py);
			break;
		}

		moveTo(getX(), getY() - 2, this);

		if (collidedWithEnemy() || collidedWithBlock())
		{
			if (collidedWithEnemy())
			{
				getWorld()->increaseScore(100);
				getWorld()->getOneCollidingEnemy(this)->setNotAlive();
			}
			setNotAlive();
			return;
		}
	}
}

void PiranhaFireball::doSomething()
{
	int dir = getDirection();
	double px = getX();
	double py = getY();

	Peach* m_peach = getWorld()->getCollidingPeach(this);

	if (isAlive())
	{
		if (collidedWithPeach() || collidedWithBlock())
		{
			if (collidedWithPeach() && !m_peach->currStarPower())
			{
				m_peach->decHealth();
				m_peach->setFlower(false);
				m_peach->setMushroom(false);
				if(m_peach->getHealth() == 0)
				{
					m_peach->setNotAlive();
					getWorld()->playSound(SOUND_PLAYER_DIE);
				}
				else
				{
					getWorld()->playSound(SOUND_PLAYER_HURT);
				}
			}
			setNotAlive();
			return;
		}

		switch (dir)
		{
		case left:
			GraphObject::moveTo(px - 2, py);
			break;
		case right:
			GraphObject::moveTo(px + 2, py);
			break;
		}

		moveTo(getX(), getY() - 2, this);

		if (collidedWithBlock())
		{
			setNotAlive();
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////
///		Enemy												///////////////////////
///////////////////////////////////////////////////////////////////////////////////

void Enemy::doSomething()
{
	int dir = getDirection();
	double px = getX();
	double py = getY();

	switch (dir)
	{
	case left:
		if (!getWorld()->isValidPos(px - 1, py, this) || getWorld()->isValidPos(px - SPRITE_WIDTH, py - 1, this))
		{
			setDirection(right);
		}
		break;
	case right:
		if (!getWorld()->isValidPos(px + 1, py, this) || getWorld()->isValidPos(px + SPRITE_WIDTH, py - 1, this))
		{
			setDirection(left);
		}
		break;
	}
	
	if (!collidedWithPeach())
	{
		switch (dir)
		{
		case left:
			moveTo(px - 1, py, this);
			break;
		case right:
			moveTo(px + 1, py, this);
			break;
		}
	}
}

void Koopa::whenDead()
{
	int dir = getDirection();
	double px = getX();
	double py = getY();

	getWorld()->addShell(px / SPRITE_WIDTH, py / SPRITE_HEIGHT, dir);
}

void Piranha::doSomething()
{
	GraphObject::increaseAnimationNumber();

	if (withinRange(getWorld()->getPeach()))
	{
		shootFire();
	}
}

void Piranha::shootFire()
{
	if (fireDelay > 0)
	{
		fireDelay--;
		return;
	}

	getWorld()->playSound(SOUND_PIRANHA_FIRE);

	int dir = getDirection();
	double px = getX();
	double py = getY();
	
	getWorld()->addPiranhaFireball(px / SPRITE_WIDTH, py / SPRITE_HEIGHT, dir);
	
	fireDelay = 40;
}

bool Piranha::withinRange(Actor* a)
{
	if ((getWorld()->getPeach()->getY() < getY() + 1.5 * SPRITE_HEIGHT) && (getWorld()->getPeach()->getY() > getY() - 1.5 * SPRITE_HEIGHT))
	{
		if (getWorld()->getPeach()->getX() < getX() && getWorld()->getPeach()->getX() > getX() - 8 * SPRITE_WIDTH)
		{
			setDirection(left);
			return true;
		}
		if (getWorld()->getPeach()->getX() > getX() && getWorld()->getPeach()->getX() < getX() + 8 * SPRITE_WIDTH)
		{
			setDirection(right);
			return true;
		}
	}
	return false;
}