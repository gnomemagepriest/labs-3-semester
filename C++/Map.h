#pragma once
#include "Tile.h"
#include <vector>

class Map {
    friend class Game;
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
    int getWidth();
    int getHeigth();
    Tile* getTile(int x, int y);
    void setTile(int x, int y, Tile newTile);
    void displayMap();
    bool generateDungeonLevel(int maxFeatures);
};