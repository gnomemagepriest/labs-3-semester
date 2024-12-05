#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

class Map {
private:
    std::vector<std::vector<Tile>> tiles;
    int startX;
    int startY;
    int width;
    int height;

public:
    Map(int width, int height, int startX, int startY);
    void setTile(int x, int y, TileType type);
    void displayMap();
    bool generateDungeonLevel(int roomCount);
};