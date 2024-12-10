#include "Enemy.h"
#include "Map.h"

Enemy::Enemy() {
	Name = "Zombie";
	Health = 5;
	Defense = 1;
	Level = 1;
	Agression = 100;
	XPValue = 50;
	Symbol = 'Z';
}

void Enemy::move(Map* map, int dx, int dy) {
	int newX = x + dx;
	int newY = y + dy;
	if (map->getTile(newX, newY).isWalkable() || !map->getTile(newX, newY).hasEntity()) {
		map->getTile(x, y).deleteEntity();
		map->setTile(newX, newY, this);
		x = newX;
		y = newY;
	}
}

void Enemy::makeTurn(Map* map, Logger& logger) {
	move(map, rand() % 3 - 1, rand() % 3 - 1);
}

int Enemy::getLevel() {
	return Level;
}

int Enemy::getXPValue() {
	return XPValue;
}
