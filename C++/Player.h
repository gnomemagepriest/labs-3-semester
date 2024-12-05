#pragma once
#include "Entity.h"
#include "Enemy.h"

class Player : public Entity {
private:
	int XP;
public:
	Player();
	void move(int dx, int dy) const override;
	void makeTurn(Logger& logger) const override;
	void getXP(Enemy& enemy);
};

