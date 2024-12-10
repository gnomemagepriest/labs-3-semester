#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Map.h"
#include "Logger.h"

class Game
{
private:
	Logger logger;
	Map level1 = Map(40, 20);
	Player player;
	std::vector<Enemy> enemies;
	bool running;
	void getInput();
	void placeEnemies();
public:
	char input;
	Game();
	void run();
	Map* getMap();
};

