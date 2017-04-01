#include "Dragon.h"

Dragon::Dragon() : Enemy() {

}

Dragon::Dragon(int health, int strength, int magic) : Enemy(health, strength, magic) {
	//Adds a unique random prefix to the enemy's name based on enemy type
	std::string rank = "";
	int randRank = rand() % 2;
	if (randRank == 0) {
		rank = "Baby";
	}
	else {
		rank = "Red";
	}
	setRank(rank);
}

//Dragon attacks all targets and applies damage to all targets
void Dragon::attack(std::vector<Character*> targets) {

	std::vector<Character*>::iterator iter;
	int damage = 0;

	for (Character* target : targets) {

		//Ensures Dragon doesn't attack itself
		if (target != this) {
			//Example damage calculation involving strength and magic stats of both characters
			damage = 5 + (((getStrength() + getMagic()) / 10) - ((target->getStrength() + target->getMagic()) / 20));
			damageTarget(target, damage);
		}
	}
}