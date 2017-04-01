#include "Character.h"

void Character::damageTarget(Character * target, int damage)
{
	target->setHealth(target->getHealth() - damage);
}

Character::Character() {
	m_health = 0;
	m_strength = 0;
	m_magic = 0;
}

Character::Character(int health, int strength, int magic) {
	m_health = health;
	m_strength = strength;
	m_magic = magic;
}

int Character::getHealth() {
	return m_health;
}

void Character::setHealth(int health) {
	m_health = health;
}

int Character::getStrength() {
	return m_strength;
}

void Character::setStrength(int strength) {
	m_strength = strength;
}

int Character::getMagic() {
	return m_magic;
}

void Character::setMagic(int magic) {
	m_magic = magic;
}

void Character::attack(std::vector<Character*> targets) {

}