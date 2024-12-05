#pragma once
#include "Entity.h"

//class Player;

class Enemy : public Entity
{
private:
	int XPValue;
	int Agression;
public:
	Enemy();
	void move(int dx, int dy) const override;
	void makeTurn(Logger& logger) const override;
	//friend void Player::getXP(const Enemy& enemy);
	int getLevel();
	int getXPValue();
};

