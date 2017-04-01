#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <vector>


class Character {
protected:
	int m_health, m_strength, m_magic;
	virtual void damageTarget(Character* target, int damage);
public:
	Character();
	Character(int health, int strength, int magic);
	int getHealth();
	void setHealth(int health);
	int getStrength();
	void setStrength(int strength);
	int getMagic();
	void setMagic(int magic);
	virtual void attack(std::vector<Character*> targets);
};

#endif
