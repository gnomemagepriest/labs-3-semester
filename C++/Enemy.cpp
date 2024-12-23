#include "Enemy.h"

Enemy::Enemy() : Entity() {
	Name = "Zombie";
	Health = 5;
	Defense = 1;
	Level = 1;
	Agression = 100;
	XPValue = 50;
	Symbol = 'Z';
}

int Enemy::getLevel() {
	return Level;
}

int Enemy::getXPValue() {
	return XPValue;
}
