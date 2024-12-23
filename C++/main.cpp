#include <iostream>
#include "Game.h"

int main() {
    try {
        Game* game = new Game();

        if (!game) {
            throw std::runtime_error("Игра не была инициализована.");
        }

        game->run();

        delete game;
    }
    catch (std::runtime_error e) {
        std::cout << "Произошла ошибка времени выполнения. Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
