#include "Enemy.h"

Enemy::Enemy() : Entity() {
	Name = "Zombie";
	Health = 10;
	Defense = 1;
	Level = 1;
	Agression = 100;
	XPValue = 51;
	Attack = 10;
	Symbol = 'Z';
}

Enemy::Enemy(int health, int attack, int defense, int level, int XPValue, int Agression, std::string Name, char Symbol) 
	: Entity(Name, health, defense, attack, level, Symbol), XPValue(), Agression() {}

void Enemy::onLevelUp() {
	Attack += 1;
	Health += 5;
	XPValue += 50;
}

Enemy& Enemy::operator=(const Enemy& other) {
	if (this == &other) {
		return *this;
	}
	Entity::operator=(other); // Копируем базовую часть
	XPValue = other.XPValue;
	Agression = other.Agression;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
	os << static_cast<const Entity&>(enemy);
	os << "XP value: " << enemy.XPValue << "\n";
	return os;
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
