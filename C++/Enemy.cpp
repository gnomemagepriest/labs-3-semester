#include "Enemy.h"

Enemy::Enemy() : Entity() {
	Name = "Zombie";
	Health = 10;
	Defense = 1;
	Level = 1;
	Agression = 100;
	XPValue = 50;
	Attack = 10;
	Symbol = 'Z';
}

int Enemy::getLevel() {
	return Level;
}

int Enemy::getXPValue() {
	return XPValue;
}

bool Enemy::operator==(const Enemy& other) const {
	return this->getPosition() == other.getPosition();
}
