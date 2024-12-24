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
	return &Level; // ���������� ��������� �� �������
}

int& Player::getHealthRef() {
	return Health; // ���������� ������ �� ��������
}

void Player::gainXP(int amount) {
	XP += amount;
	if (XP % 100 > Level) {
		Level += 1;
		onLevelUp();
	}
}
