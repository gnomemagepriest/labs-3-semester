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

std::string Player::getInventoryDescription() {
	if (Inventory.empty()) {
		return "You don't have any items.";
	}

	std::string result = "You have: \n";
	for (const auto& item : Inventory) {
		result += "- " + item->getName() + "\n";
	}
	return result;
}

int* Player::getLevelPtr() {
	return &Level; // Возвращаем указатель на уровень
}

int& Player::getHealthRef() {
	return Health; // Возвращаем ссылку на здоровье
}