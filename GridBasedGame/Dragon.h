#ifndef DRAGON_H
#define DRAGON_H

#include <iostream>
#include <string>

#include "Enemy.h"

class Dragon : public Enemy {
public:
	Dragon();
	Dragon(int health, int strength, int magic);
	virtual void attack(std::vector<Character*> targets);
};

#endif
