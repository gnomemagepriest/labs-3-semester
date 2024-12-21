#include "Tile.h"

Tile::Tile(TileType typeOfTile) {
	Type = typeOfTile;
	entity = nullptr;
}

Tile::Tile(Entity* entityOnTile) {
	Type = TileType::FLOOR;
	entity = entityOnTile;
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

void Tile::placeEntity(Entity* newEntity) {
	entity = newEntity;
}

void Tile::deleteEntity() {
	entity = nullptr;
}

void Tile::deleteItems() {
	items.clear();
}

std::vector<Item> Tile::getItems()
{
	return items;
}
