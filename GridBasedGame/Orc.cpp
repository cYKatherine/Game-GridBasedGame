#include "Orc.h"

Orc::Orc() : Enemy() {

}

Orc::Orc(int health, int strength, int magic) : Enemy(health, strength, magic) {
	//Adds a unique random suffix to the enemy's name based on enemy type
	std::string rank = "";
	int randRank = rand() % 2;
	if (randRank == 0) {
		rank = "Grunt";
	}
	else {
		rank = "Berserker";
	}
	setRank(rank);
}

//Orc always attacks the player (something that doesn't subclass Enemy)
void Orc::attack(std::vector<Character*> targets) {

	// find the player
	Character* target = NULL;
	for (Character* t : targets) {
		Enemy* enemy = dynamic_cast<Enemy*>(t);
		if (!enemy) target = t;
	}

	//Example damage calculation involving strength and magic stats of both characters
	int damage = 5 + (((getStrength() + getMagic()) / 10) - ((targets[0]->getStrength() + targets[0]->getMagic()) / 20));

	damageTarget(target, damage);
}