#include "Enemy.h"

Enemy::Enemy() {
	m_health = 0;
	m_strength = 0;
	m_magic = 0;
	m_rank = "";
}

Enemy::Enemy(int health, int strength, int magic) : Character(health, strength, magic) {
	m_health = health;
	m_strength = strength;
	m_magic = magic;
	m_rank = "";
}

void Enemy::damageTarget(Character * target, int damage)
{
	target->setHealth(target->getHealth() - damage);
}

void Enemy::attack(std::vector<Character*> targets) {
}

std::string Enemy::getRank() {
	return m_rank;
}

void Enemy::setRank(std::string rank) {
	m_rank = rank;
}

int Enemy::getHealth() {
	return m_health;
}

void Enemy::setHealth(int health) {
	m_health = health;
}

int Enemy::getStrength() {
	return m_strength;
}

void Enemy::setStrength(int strength) {
	m_strength = strength;
}

int Enemy::getMagic() {
	return m_magic;
}

void Enemy::setMagic(int magic) {
	m_magic = magic;
}