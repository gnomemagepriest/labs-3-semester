#include "Entity.h"
#include <iostream>

Entity& Entity::takeDamage(int damageTaken) {
	damageTaken -= Defense;
	if (damageTaken > 0) {
		this->Health -= damageTaken;
	}
	return *this;
}

Entity& Entity::operator=(const Entity& other) {
	if (this == &other) {
		return *this;
	}
	Name = other.Name;
	Health = other.Health;
	Defense = other.Defense;
	Attack = other.Attack;
	Level = other.Level;
	x = other.x;
	y = other.y;
	Symbol = other.Symbol;
	inventory = other.inventory;
	return *this;
}

char Entity::getChar() {
	return Symbol;
}

std::string Entity::getName() {
	return Name;
}

int Entity::getHealth() {
	return Health;
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
	totalEntities++;
}

Entity::Entity(std::string Name, int Health, int Defense, int Attack, int Level, char Symbol)
	: Name(Name), Health(Health), Defense(Defense), Attack(Attack), Level(Level), Symbol(Symbol) {
	totalEntities++;
}

int Entity::getTotalEntities() {
	return totalEntities;
}

std::ostream& operator<<(std::ostream& os, const Entity& entity) {
	os << "Name: " << entity.Name << "\n"
		<< "Health: " << entity.Health << "\n"
		<< "Defense: " << entity.Defense << "\n"
		<< "Attack: " << entity.Attack << "\n"
		<< "Level: " << entity.Level << "\n"
		<< "Position: (" << entity.x << ", " << entity.y << ")\n"
		<< "Symbol: " << entity.Symbol << "\n";
	return os;
}
