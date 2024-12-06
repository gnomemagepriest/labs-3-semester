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
	Map level1;
	Player player;
};

