#ifndef GIANTSPIDER_H
#define GIANTSPIDER_H

#include <iostream>
#include <string>

#include "Enemy.h"

class GiantSpider : public Enemy {
public:
	GiantSpider();
	GiantSpider(int health, int strength, int magic);
	virtual void attack(std::vector<Character*> targets);
};

#endif
