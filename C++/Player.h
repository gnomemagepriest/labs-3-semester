#pragma once
#include "Entity.h"

class Player : public Entity {
private:
	int XP;
	char input;
public:
	Player();
	//void getXP(Enemy& enemy);
	bool isAlive();
	void setInput(char newInput);
	std::string getInventoryDescription();
};

