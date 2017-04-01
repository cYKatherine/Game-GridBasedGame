#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include "Character.h"
#include <string>

class Enemy : public Character{
private:
	int m_health, m_strength, m_magic;
	std::string m_rank;
protected:
	void setRank(std::string rank);
public:
	Enemy();
	Enemy(int health, int strength, int magic);

	virtual void attack(std::vector<Character*> targets);
	virtual void damageTarget(Character * target, int damage);

	std::string getRank();
	int getHealth();
	void setHealth(int health);
	int getStrength();
	void setStrength(int strength);
	int getMagic();
	void setMagic(int magic);
};

#endif
