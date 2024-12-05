#include "Player.h"

Player::Player() {

}

void Player::move(int dx, int dy) const {

}

void Player::makeTurn(Logger& logger) const {

}

void Player::getXP(Enemy& enemy) {
	XP += (enemy.getLevel() / Level) * enemy.getXPValue();
}
