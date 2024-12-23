#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <tuple>

Game::Game() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	map.generateDungeonLevel(30);
	input = 0;
	placeFeatures();
	running = true;
}

void Game::playerTurn() {
	int dx = 0, dy = 0;

	switch (input)
	{
	case 'w': {
		dy = -1;
		break;
	}
	case 's': {
		dy = 1;
		break;
	}
	case 'a': {
		dx = -1;
		break;
	}
	case 'd': {
		dx = 1;
		break;
	}
	default:
		break;
	}

	moveEntity(&player, dx, dy);
}

void Game::moveEntity(Entity* entity, int dx, int dy) {
	int newX = entity->getPosition().first + dx;
	int newY = entity->getPosition().second + dy;
	Tile* newTile = map.getTile(newX, newY);
	if (!newTile)
		return;

	if (newX >= 0 && newY >= 0 && newTile->isWalkable() && !newTile->hasEntity()) {

		if (newTile->hasItems()) {
			for (Item item : newTile->getItems()) {
				entity->addItem(item);
				logger.addLine(entity->getName() + " has picked up " + item.getName());
			}
			newTile->deleteItems();
		}
		map.getTile(
			entity->getPosition().first, 
			entity->getPosition().second)
			->deleteEntity();
		newTile->placeEntity(entity);
		entity->setPosition(newX, newY);
	}
}

Map* Game::getMap() {
	return &map;
}

void Game::getInput() {
	input = getchar();
	while (getchar() != '\n');
}

void Game::placeFeatures() {
	for (int k = 0; k < 10; k++)
		enemies.push_back(Enemy());

	std::vector<std::pair<int, int>> freeTiles;

	for (int y = 0; y < map.height; y++) {
		for (int x = 0; x < map.width; x++) {
			if (!map.getTile(x, y)->hasEntity() && map.getTile(x, y)->isWalkable()) {
				freeTiles.push_back(std::pair<int, int>(x, y));
			}
		}
	}

	for (int i = freeTiles.size() - 1; i >= 1; i--) {
		int j = rand() % (i + 1);
		std::swap(freeTiles[j], freeTiles[i]);
		
	}

	int totalEntities = enemies.size() + 1 + 3; // +1 для игрока + 3 для предметов (временно)
	if (freeTiles.size() < totalEntities) {
		throw std::runtime_error("Недостаточно свободных клеток"); // Выход из функции, если недостаточно клеток
	}
	
	int i = 0;
	for (Enemy& enemy : enemies) {
		enemy.setPosition(freeTiles[i].first, freeTiles[i].second);
		map.getTile(freeTiles[i].first, freeTiles[i].second)->placeEntity(&enemy);
		i++;
	}

	std::vector<Item> itemsToPlace = {Item("Dagger"), Item("Potion"), Item("Shield")};
	for (Item item : itemsToPlace) {
		map.getTile(std::get<0>(freeTiles[i]), std::get<1>(freeTiles[i]))->addItem(item);
		i++;
	}

	player.setPosition(freeTiles[i].first, freeTiles[i].second);
	map.getTile(freeTiles[i].first, freeTiles[i].second)->placeEntity(&player);
}

void Game::run() {
	while (running && player.isAlive()) {
		//system("cls");
		map.displayMap();
		std::cout << logger.getLastEvents() << "Input: " << std::endl;

		getInput();
		switch (input)
		{
		case 'q':
			running = false;
			break;
		case 'i':
			std::cout << player.getInventoryDescription();
			
			break;
		case '~':
			std::cout << "DEBUG MODE\n";
			getDebugValues();
			break;
		default:
		{
			playerTurn();
			break;
		}
		}

		for (auto& enemy : enemies) {
			// Случайное перемещение врагов
			moveEntity(&enemy, rand() % 3 - 1, rand() % 3 - 1);
		}
	}
}

void Game::getDebugValues() {
	getInput();
	switch (input)
	{
	case '1':
		std::cout << "Created entities: " << Entity::getTotalEntities();
		break;
	}

	while (getchar() != '\n');
}