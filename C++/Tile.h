#pragma once
#include <vector>
#include "Entity.h"
#include <memory>

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
	std::vector<std::shared_ptr<Item>> items;
public:
	Tile(TileType typeOfTile);
	Tile(Entity* entityOnTile);
	void addItem(std::shared_ptr<Item> item);
	bool hasEntity();
	bool hasItems();
	bool isWalkable();
	void onMove();
	void placeEntity(Entity* newEntity);
	void deleteEntity();
	void deleteItems();
	std::vector<std::shared_ptr<Item>> getItems();
};

