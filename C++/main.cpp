#include <iostream>
#include "Game.h"

int main() {
    Game* game = new Game();

    if (!game) {
        return 1;
    }
    
    game->run();

    delete[] game;

    return 0;
}
