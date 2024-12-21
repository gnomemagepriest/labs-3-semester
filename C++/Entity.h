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
	char Symbol;
	std::vector<Item> Inventory;
public: 
	bool takeDamage(int damageTaken);
	char getChar();
	std::string getName();
	int x, y;
	void addItem(Item item);
};

