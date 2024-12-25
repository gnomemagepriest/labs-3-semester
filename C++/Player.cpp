#include "Player.h"
#include <iostream>

Player::Player() : Entity() {
	Health = 50;
	Defense = 5;
	Level = 1;
	XP = 0;
	Name = "Player";
	Symbol = '@';
	Attack = 5;
	x = 10;
	y = 10;
}

bool Player::isAlive() {
	return Health > 0;
}

void Player::setInput(char newInput) {
	input = newInput;
}

void Player::onLevelUp() {
	Attack += 1;
	Health += 10;
}

int* Player::getLevelPtr() {
	return &Level; // Возвращаем указатель на уровень
}

int& Player::getHealthRef() {
	return Health; // Возвращаем ссылку на здоровье
}

void Player::gainXP(int amount) {
	XP += amount;
	if (XP % 100 > Level) {
		Level += 1;
		onLevelUp();
	}
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
	os << "Player XP: " << player.XP 
		<< "\nPlayer level: " << player.Level << "\n";
	return os;
}