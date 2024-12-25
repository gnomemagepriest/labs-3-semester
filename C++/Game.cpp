#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <tuple>

void attackEnemy(Player& player, Enemy& enemy) {
	int damage = player.Attack;
	enemy.takeDamage(damage);
	if (enemy.Health <= 0) {
		player.gainXP(enemy.XPValue);
		enemy.Health = 0;
	}
}

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

	int targetX = player.getPosition().first + dx;
	int targetY = player.getPosition().second + dy;
	if (map.getTile(targetX, targetY)->hasEntity()) {
		for (Enemy& enemy : enemies) {
			if (enemy.getPosition() != std::pair<int, int>(targetX, targetY))
				continue;

			int prevHealth = enemy.getHealth();
			attackEnemy(player, enemy);
			int newHealth = enemy.getHealth();
			logger.addLine("You dealt " + std::to_string(prevHealth-newHealth) + " damage to "
				+ enemy.getName() + "(" + std::to_string(newHealth) +" left)");
			if (newHealth <= 0) {
				logger.addLine(enemy.getName() + " is dead now");
				for (const auto& item : enemy.inventory.getItems()) {
					map.getTile(targetX, targetY)->addItem(item);
				}
				map.getTile(targetX, targetY)->deleteEntity();
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
			}
		}
	}
	else {
		moveEntity(&player, dx, dy);
	}
}

void Game::moveEntity(Entity* entity, int dx, int dy) {
	int newX = entity->getPosition().first + dx;
	int newY = entity->getPosition().second + dy;
	Tile* newTile = map.getTile(newX, newY);
	if (!newTile)
		return;

	if (newX >= 0 && newY >= 0 && newTile->isWalkable() && !newTile->hasEntity()) {

		if (newTile->hasItems()) {
			for (auto& item : newTile->getItems()) {
				entity->inventory.addItem(item);
				logger.addLine(entity->getName() + " has picked up " + item->getName());
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

	int totalEntities = enemies.size() + 1 + 6; // +1 для игрока + 3 для предметов
	if (freeTiles.size() < totalEntities) {
		throw std::runtime_error("Недостаточно свободных клеток"); // Выход из функции, если недостаточно клеток
	}
	
	int i = 0;
	for (Enemy& enemy : enemies) {
		enemy.setPosition(freeTiles[i].first, freeTiles[i].second);
		map.getTile(freeTiles[i].first, freeTiles[i].second)->placeEntity(&enemy);
		i++;
	}

	std::vector<std::shared_ptr<Item>> itemsToPlace = {
		std::make_shared<Item>(Item("Book of Enlightenment")),
		std::make_shared<Item>(Item("Shield"))
	};
	for (auto item : itemsToPlace) {
		map.getTile(std::get<0>(freeTiles[i]), std::get<1>(freeTiles[i]))->addItem(item);
		i++;
	}
	std::vector<std::shared_ptr<Weapon>> weaponsToPlace = {
		std::make_shared<Weapon>(Weapon("Dagger",2)),
		std::make_shared<Weapon>(Weapon("Sword",5))
	};
	for (auto item : weaponsToPlace) {
		map.getTile(std::get<0>(freeTiles[i]), std::get<1>(freeTiles[i]))->addItem(item);
		i++;
	}
	std::vector<std::shared_ptr<Potion>> potionsToPlace = {
		std::make_shared<Potion>(Potion("Murky", "Flame")),
		std::make_shared<Potion>(Potion("Yellow", "Levitation"))
	};
	for (auto item : potionsToPlace) {
		map.getTile(std::get<0>(freeTiles[i]), std::get<1>(freeTiles[i]))->addItem(item);
		i++;
	}

	player.setPosition(freeTiles[i].first, freeTiles[i].second);
	map.getTile(freeTiles[i].first, freeTiles[i].second)->placeEntity(&player);
}

void Game::run() {
	while (running && player.isAlive()) {
		system("cls");
		map.displayMap();
		std::cout << logger.getLastEvents() << "Input: " << std::endl;

		getInput();
		switch (input)
		{
		case 'q':
			running = false;
			break;
		case 'i':
			std::cout << player.inventory.getDescription();
			while (getchar() != '\n');
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
	Weapon dagger("Dagger", 2);
	Weapon doubleDagger;
	getInput();
	switch (input)
	{
	case '1':
		std::cout << "Created entities: " << Entity::getTotalEntities();
		break;
	case '2':
		std::cout << "Player level: " << *player.getLevelPtr()
			<< "\nPlayer health: " << player.getHealthRef() << std::endl;
		break;
	case '3':
		std::cout << "Player health before takeDamage: " << player.getHealthRef() << std::endl;
		player.takeDamage(10).takeDamage(10);
		std::cout << "Player health after takeDamage: " << player.getHealthRef() << std::endl;
		break;
	case '4':
		
		std::cout << "Simple dagger: " << dagger.getName() << std::endl;
		doubleDagger = dagger + dagger;
		std::cout << "Double dagger: " << doubleDagger.getName() << std::endl;
		std::cout << "Double dagger (prefix ++): " << (++doubleDagger).getName() << std::endl;
		std::cout << "Double dagger (postfix ++): " << (doubleDagger++).getName() << std::endl;
		std::cout << "Double dagger (after postfix ++): " << doubleDagger.getName() << std::endl;
		break;
	case '5':
		std::cout << player;
		break;
	}

	while (getchar() != '\n');
}
