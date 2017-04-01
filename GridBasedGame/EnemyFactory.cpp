#include "EnemyFactory.h"
#include "GiantSpider.h"
#include "Dragon.h"
#include "Orc.h"

EnemyFactory* EnemyFactory::instance = NULL;

EnemyFactory::EnemyFactory() {}

EnemyFactory* EnemyFactory::getInstance() {
	return EnemyFactory::instance == NULL ? instance = new EnemyFactory() : instance;
}

Enemy* EnemyFactory::makeEnemy() {
	switch (rand() % 3 + 1) {
	case 1: return new Dragon(rand() % 100 + 60, rand() % 120 + 60, rand() % 100);
	case 2: return new Orc(rand() % 100 + 60, rand() % 120 + 60, rand() % 100);
	case 3: return new GiantSpider(rand() % 100 + 60, rand() % 120 + 60, rand() % 100);
	}
}