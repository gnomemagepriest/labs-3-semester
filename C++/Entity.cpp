#include "Entity.h"

bool Entity::takeDamage(int damageTaken) {
	damageTaken -= Defense;
	if (damageTaken > 0) {
		Health -= damageTaken;
		return true;
	}
	return false;
}

char Entity::getChar() {
	return Symbol;
}

std::string Entity::getName() {
	return Name;
}

void Entity::addItem(Item item) {
	Inventory.push_back(item);
}

std::pair<int, int> Entity::getPosition() const {
	return { x, y };
}

void Entity::setPosition(int newX, int newY) {
	x = newX;
	y = newY;
}