#include "Map.h"

Map::Map(int width, int height, int startX, int startY)
    : width(width), height(height), startX(startX), startY(startY) {
    tiles.resize(height, std::vector<Tile>(width, Tile(TileType::FLOOR)));
}

void Map::setTile(int x, int y, TileType type) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y][x] = Tile(type);
    }
}

void Map::displayMap() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char symbol;
            Tile currentTile = tiles[y][x];
            switch (currentTile.Type) {
            case TileType::WALL: symbol = '#'; break;
            case TileType::FLOOR: symbol = '.'; break;
            case TileType::DOOR: symbol = '+'; break;
            default: break;
            }

            if (currentTile.player) {
                symbol = currentTile.player->getChar();
            }
            else if (currentTile.entity) {
                symbol = currentTile.entity->getChar();
            }

            std::cout << symbol << ' ';
        }
        std::cout << std::endl;
    }
}

bool generateDungeonLevel(int roomCount) {
    return false;
}