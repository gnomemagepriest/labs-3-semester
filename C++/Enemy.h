#pragma once
#include "Entity.h"

class Player;

class Enemy : public Entity
{
private:
	int XPValue;
	int Agression;
public:
	Enemy();
	int getLevel();
	int getXPValue();
	friend void attackEnemy(Player& player, Enemy& enemy);
	bool operator==(const Enemy& other) const;
};

