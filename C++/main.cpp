#include <iostream>
#include "Map.h"

int main() {
    Map dungeon(40, 20);
    dungeon.generateDungeonLevel(20);
    dungeon.displayMap();

    return 0;
}
