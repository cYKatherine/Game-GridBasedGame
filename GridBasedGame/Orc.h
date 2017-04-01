#ifndef ORC_H
#define ORC_H

#include <iostream>
#include <string>

#include "Enemy.h"

class Orc : public Enemy {
public:
	Orc();
	Orc(int health, int strength, int magic);
	virtual void attack(std::vector<Character*> targets);
};

#endif
