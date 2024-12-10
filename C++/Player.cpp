#include "Player.h"
#include "Map.h"

Player::Player() {
	Health = 50;
	Defense = 5;
	Level = 1;
	XP = 0;
	Name = "Player";
	Symbol = '@';
	x = 10;
	y = 10;
}

void Player::move(Map* map, int dx, int dy) {
	int newX = x + dx;
	int newY = y + dy;
	if (newX > 0 && newY > 0
		&& map->getTile(newX, newY).isWalkable() && !map->getTile(newX, newY).hasEntity()) {
		map->getTile(x, y).deleteEntity();
		map->setTile(newX, newY, this);
		x = newX;
		y = newY;
	}
}

void Player::makeTurn(Map* map, Logger& logger) {

	int dx = 0, dy = 0;

	switch (input)
	{
	case 'w': {
		dy = 1;
		break;
	}
	case 's': {
		dy = -1;
		break;
	}
	case 'a': {
		dx = -1;
		break;
	}
	case 'd': {
		dx = 1;
		break;
	}
	default:
		break;
	}

	move(map, dx, dy);
}

//void Player::getXP(Enemy& enemy) {
//	XP += (enemy.getLevel() / Level) * enemy.getXPValue();
//}

bool Player::isAlive() {
	return Health > 0;
}

void Player::setInput(char newInput){
	input = newInput;
}
