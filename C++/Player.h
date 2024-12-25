#pragma once
#include "Entity.h"

class Enemy;

class Player : public Entity {
private:
	int XP;
	char input;
	void onLevelUp() override;
public:
	Player();
	bool isAlive();
	void setInput(char newInput);
	int* getLevelPtr(); // Возврат уровня через указатель
	int& getHealthRef(); // Возврат здоровья через ссылку
	friend void attackEnemy(Player& player, Enemy& enemy);
	void gainXP(int amount);
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

