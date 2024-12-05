#include "Tile.h"

Tile::Tile(TileType typeOfTile) {
	Type = typeOfTile;
	player = nullptr;
	entity = nullptr;
}

Tile::Tile(Player* playerOnTile, Entity* entityOnTile) {
	Type = TileType::FLOOR;
	player = playerOnTile;
	entity = entityOnTile;
}

bool Tile::hasPlayer() {
	return player != nullptr;
}

bool Tile::hasEntity() {
	return entity != nullptr;
}

bool Tile::hasItems() {
	return !items.empty();
}

bool Tile::isWalkable() {
	return Type != TileType::WALL;
}

void Tile::addItem(Item newItem) {
	items.push_back(newItem);
}

void Tile::onMove() {
	if (Type == TileType::DOOR) {
		Type = TileType::FLOOR;
	}
}