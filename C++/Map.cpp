#include "Map.h"
#include <iostream>
#include <cstdlib>

// Заполнение карты стеной
Map::Map(int width, int height) : width(width), height(height) {
    tiles.resize(height, std::vector<Tile>(width, Tile(TileType::WALL)));
}

int Map::getWidth() {
    return width;
}

int Map::getHeigth() {
    return height;
}

void Map::setTile(int x, int y, Tile newTile) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y][x] = newTile;
    }
}

Tile* Map::getTile(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return &tiles[y][x];
    }
    return nullptr;
}

Tile* Map::getTile(std::pair<int, int> position) {
    int x = position.first;
    int y = position.second;
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return &tiles[y][x];
    }
    return nullptr;
}

void Map::displayMap() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char symbol = ' ';
            Tile& currentTile = tiles[y][x];
            if (currentTile.hasEntity()) {
                symbol = currentTile.entity->getChar();
            }
            else if (currentTile.hasItems()) {
                symbol = currentTile.getItems()[0]->getSymbol();
            }
            else {
                switch (currentTile.Type) {
                case TileType::FLOOR: symbol = '.'; break;
                case TileType::DOOR: symbol = '+'; break;
                }
            }

            std::cout << symbol;
        }
        std::cout << std::endl;
    }
}

void Map::createCorridor(int x1, int y1, int x2, int y2) {
    // Создание коридора от (x1, y1) до (x2, y2)
    if (x1 > x2) std::swap(x1, x2); //  x1 <= x2
    if (y1 > y2) std::swap(y1, y2); //  y1 <= y2
    int x, y;
    // Если коридор горизонтальный
    for (x = x1; x <= x2; ++x) {
        setTile(x, y1, TileType::FLOOR);
    }

    // Если коридор вертикальный
    for (y = y1; y <= y2; ++y) {
        setTile(x2, y, TileType::FLOOR);
    }

}

bool Map::generateDungeonLevel(int maxFeatures) {
    // Выкапываем одну комнату в центре карты
    int roomWidth = 5 + std::rand() % 6;
    int roomHeight = 5 + std::rand() % 6;
    int roomX = (width - roomWidth) / 2;
    int roomY = (height - roomHeight) / 2;

    Room initialRoom = { roomX, roomY, roomWidth, roomHeight };
    rooms.push_back(initialRoom);

    for (int y = roomY; y < roomY + roomHeight; ++y) {
        for (int x = roomX; x < roomX + roomWidth; ++x) {
            tiles[y][x].Type = TileType::FLOOR;
        }
    }

    for (int i = 0; i < maxFeatures; ++i) {
        Room& room = rooms[std::rand() % rooms.size()];

        int wall = std::rand() % 4;

        Room newRoom;
        switch (wall) {
        case 0: // Верхняя стена
            newRoom.x = room.x + std::rand() % room.width;
            newRoom.y = room.y - (2 + std::rand() % 3), 0; // Добавляем коридор вверх
            newRoom.width = 3 + std::rand() % 4; // Ширина нового объекта
            newRoom.height = 2 + std::rand() % 3; // Высота нового объекта
            break;
        case 1: // Нижняя стена
            newRoom.x = room.x + std::rand() % room.width;
            newRoom.y = room.y + room.height + (1 + std::rand() % 3); // Добавляем коридор вниз
            newRoom.width = 3 + std::rand() % 4;
            newRoom.height = 2 + std::rand() % 3;
            break;
        case 2: // Левая стена
            newRoom.x = room.x - (2 + std::rand() % 3); // Добавляем коридор влево
            newRoom.y = room.y + std::rand() % room.height;
            newRoom.width = 2 + std::rand() % 3;
            newRoom.height = 3 + std::rand() % 4;
            break;
        case 3: // Правая стена
            newRoom.x = room.x + room.width + (1 + std::rand() % 3); // Добавляем коридор вправо
            newRoom.y = room.y + std::rand() % room.height;
            newRoom.width = 2 + std::rand() % 3;
            newRoom.height = 3 + std::rand() % 4;
            break;
        }

        // Проверка на возможность добавления нового объекта
        bool canAdd = true;
        for (const auto& r : rooms) {
            if (newRoom.x < 0 || newRoom.y < 0 || newRoom.x + newRoom.width > width || newRoom.y + newRoom.height > height
                || !(newRoom.x + newRoom.width <= r.x || newRoom.x >= r.x + r.width ||
                newRoom.y + newRoom.height <= r.y || newRoom.y >= r.y + r.height)) {
                canAdd = false;
                break;
            }
        }

        if (canAdd) {
            int centerX1 = room.x + room.width / 2;
            int centerY1 = room.y + room.height / 2;
            int centerX2 = newRoom.x + newRoom.width / 2;
            int centerY2 = newRoom.y + newRoom.height / 2;

            createCorridor(centerX1, centerY1, centerX2, centerY2);

            rooms.push_back(newRoom);
            for (int y = newRoom.y; y < newRoom.y + newRoom.height; ++y) {
                for (int x = newRoom.x; x < newRoom.x + newRoom.width; ++x) {
                    tiles[y][x] = TileType::FLOOR;
                }
            }
        }
    }

    return true; // Успешное завершение генерации уровня
}