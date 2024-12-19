#include "Player.h"

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

bool Player::isAlive() {
	return Health > 0;
}

void Player::setInput(char newInput){
	input = newInput;
}
