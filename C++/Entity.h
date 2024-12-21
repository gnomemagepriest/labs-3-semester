#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Logger;
class Map;
class Game;

class Entity
{
protected:
	std::string Name;
	int Health, Defense, Level;
	int x, y;
	char Symbol;
	std::vector<Item> Inventory;
public: 
	bool takeDamage(int damageTaken);
	char getChar();
	std::string getName();
	void addItem(Item item);
	std::pair<int, int> getPosition() const;
	void setPosition(int newX, int newY);
};

