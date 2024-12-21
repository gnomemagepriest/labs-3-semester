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
	Map map = Map(40, 20);
	Player player;
	std::vector<Enemy> enemies;
	char input;
	bool running;
	void getInput();
	void placeFeatures();
	void moveEntity(Entity* entity, int dx, int dy);
	void playerTurn();
public:
	Game();
	void run();
	Map* getMap();
};

