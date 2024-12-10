#pragma once
#include <vector>
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
	friend class Game;
private:
	TileType Type;
	Entity* entity;
	std::vector<Item> items;
public:
	Tile(TileType typeOfTile);
	Tile(Entity* entityOnTile);
	void addItem(Item item);
	bool hasEntity();
	bool hasItems();
	bool isWalkable();
	void onMove();
	void deleteEntity();
};

