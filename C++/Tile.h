#pragma once
#include <vector>
#include "Player.h"
#include "Entity.h"
#include "Item.h"

enum class TileType {
	WALL,
	FLOOR,
	DOOR
};

class Map;

class Tile
{
	friend class Map;
private:
	TileType Type;
	Player* player;
	Entity* entity;
	std::vector<Item> items;
public:
	Tile(TileType typeOfTile);
	Tile(Player* playerOnTile, Entity* entityOnTile);
	void addItem(Item item);
	bool hasPlayer();
	bool hasEntity();
	bool hasItems();
	bool isWalkable();
	void onMove();
};

