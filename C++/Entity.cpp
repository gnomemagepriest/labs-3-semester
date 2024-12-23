#include "Entity.h"
#include <iostream>

Entity& Entity::takeDamage(int damageTaken) {
	damageTaken -= Defense;
	if (damageTaken > 0) {
		this->Health -= damageTaken;
	}
	return *this;
}

char Entity::getChar() {
	return Symbol;
}

std::string Entity::getName() {
	return Name;
}

void Entity::addItem(std::shared_ptr<Item> item) {
	Inventory.push_back(item);
}

std::pair<int, int> Entity::getPosition() const {
	return { x, y };
}

void Entity::setPosition(int newX, int newY) {
	x = newX;
	y = newY;
}

int Entity::totalEntities = 0;

Entity::Entity() {
	Inventory.clear();
	totalEntities++;
}

int Entity::getTotalEntities() {
	return totalEntities;
}
