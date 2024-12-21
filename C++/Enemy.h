#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
	int XPValue;
	int Agression;
public:
	Enemy();
	//friend void Player::getXP(const Enemy& enemy);
	int getLevel();
	int getXPValue();
};

