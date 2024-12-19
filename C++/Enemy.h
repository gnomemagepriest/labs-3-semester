#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
	int XPValue;
	int Agression;
public:
	Enemy();
	//void move(Map* map, int dx, int dy) override;
	//void makeTurn(Map* map, Logger& logger) override;
	//friend void Player::getXP(const Enemy& enemy);
	int getLevel();
	int getXPValue();
};

