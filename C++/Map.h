#pragma once
#include <vector>
#include "Tile.h"

class Map {
private:
    std::vector<std::vector<Tile>> tiles;
    int width;
    int height;

    struct Room {
        int x, y, width, height;
    };

    std::vector<Room> rooms;
    void createCorridor(int centerX1, int centerY1, int centerX2, int centerY2);
public:
    Map(int width, int height);
    void setTile(int x, int y, TileType type);
    void displayMap();
    bool generateDungeonLevel(int maxFeatures);
};