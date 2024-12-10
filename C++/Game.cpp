#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <tuple>

Game::Game() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	level1.generateDungeonLevel(30);
	player = Player();
	input = 0;
	placeEnemies();
	running = true;
}

Map* Game::getMap() {
	return &level1;
}

void Game::getInput() {
	input = getchar();
}

void Game::placeEnemies() {
	enemies.push_back(Enemy());

	std::vector<std::tuple<int, int>> freeTiles;

	for (int y = 0; y < level1.height; y++) {
		for (int x = 0; x < level1.width; x++) {
			if (!level1.getTile(x, y).hasEntity() && level1.getTile(x, y).isWalkable()) {
				freeTiles.push_back(std::tuple<int, int>(x, y));
			}
		}
	}

	for (int i = freeTiles.size() - 1; i >= 1; i--) {
		int j = rand() % (i + 1);
		std::swap(freeTiles[j], freeTiles[i]);
		
	}

	int totalEntities = enemies.size() + 1; // +1 для игрока
	if (freeTiles.size() < totalEntities) {
		std::cerr << "Недостаточно свободных клеток для размещения всех врагов и игрока." << std::endl;
		throw 3; // Выход из функции, если недостаточно клеток
	}
	
	int i = 0;
	for (Enemy enemy : enemies) {
		enemy.x = std::get<0>(freeTiles[i]);
		enemy.y = std::get<1>(freeTiles[i]);
		level1.setTile(enemy.x, enemy.y, Tile(&enemy));
		//std::cout << &enemy << " " << level1.getTile(enemy.x, enemy.y).entity << "\n";
		i++;
	}

	player.x = std::get<0>(freeTiles[i]);
	player.y = std::get<1>(freeTiles[i]);
	//level1.getTile(player.x, player.y).placeEntity(&player);
	level1.setTile(player.x, player.y, Tile(&player));
	//std::cout << &player << " " << level1.getTile(player.x, player.y).entity << "\n";
}

void Game::run() {
	while (running && player.isAlive()) {
		system("cls");
		level1.displayMap();
		std::cout << logger.getLastEvents() << "Input: " << std::endl;

		getInput();
		switch (input)
		{
		case 'q':
			running = false;
		default:
		{
			player.setInput(input);
			player.makeTurn(&level1, logger);
			break;
		}
		}

		for (auto enemy : enemies) {
			enemy.makeTurn(&level1, logger);
		}
	}
}
