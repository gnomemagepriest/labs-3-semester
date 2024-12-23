#include "Player.h"
#include <iostream>

Player::Player() : Entity() {
	std::cout << "it is player\n";
	Health = 50;
	Defense = 5;
	Level = 1;
	XP = 0;
	Name = "Player";
	Symbol = '@';
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
	for (Item item : Inventory) {
		result += "- " + item.getName() + "\n";
	}
	return result;
}

int* Player::getLevelPtr() {
	return &Level; // Возвращаем указатель на уровень
}

int& Player::getHealthRef() {
	return Health; // Возвращаем ссылку на здоровье
}
