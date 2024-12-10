#pragma once
#include "Entity.h"

class Enemy;

class Player : public Entity {
private:
	int XP;
	char input;
public:
	Player();
	void move(Map* map, int dx, int dy) override;
	void makeTurn(Map* map, Logger& logger) override;
	void getXP(Enemy& enemy);
	bool isAlive();
	void setInput(char newInput);
};

