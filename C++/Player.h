#pragma once
#include "Entity.h"

class Enemy;

class Player : public Entity {
private:
	int XP;
	char input;
public:
	Player();
	bool isAlive();
	void setInput(char newInput);
	std::string getInventoryDescription();
	int* getLevelPtr(); // Возврат уровня через указатель
	int& getHealthRef(); // Возврат здоровья через ссылку
	friend void attackEnemy(Player& player, Enemy& enemy);
};

