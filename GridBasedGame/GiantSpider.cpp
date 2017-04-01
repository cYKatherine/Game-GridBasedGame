#include "GiantSpider.h"

GiantSpider::GiantSpider() : Enemy() {
}

GiantSpider::GiantSpider(int health, int strength, int magic) : Enemy(health, strength, magic) {
	std::string rank = "";
	int randRank = rand() % 2;
	if (randRank == 0) {
		rank = "Hatchling";
	}
	else {
		rank = "Queen";
	}
	setRank(rank);
}

//Giant Spider randomly chooses a target and applies damage to that target
void GiantSpider::attack(std::vector<Character*> targets) {
	Character* target = NULL;

	// Pick a target at random but not ourselves!
	while (!target || target == this) {
		target = targets[rand() % targets.size()];
	}


	//Example damage calculation involving strength and magic stats of both characters
	int damage = 5 + (((getStrength() + getMagic()) / 10) - ((target->getStrength() + target->getMagic()) / 20));

	damageTarget(target, damage);
}