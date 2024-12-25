#pragma once
#include "Entity.h"

class Player;

class Enemy : public Entity
{
private:
	int XPValue;
	int Agression;
	virtual void onLevelUp() override;
public:
	Enemy();
	Enemy(int health, int attack, int defense, int level, int XPValue, int Agression, std::string Name, char Symbol);
	Enemy& operator=(const Enemy& other);
	friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
	int getLevel();
	int getXPValue();
	friend void attackEnemy(Player& player, Enemy& enemy);
	bool operator==(const Enemy& other) const;
};

