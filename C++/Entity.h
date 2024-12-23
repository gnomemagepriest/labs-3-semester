#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Entity
{
protected:
	std::string Name;
	int Health, Defense, Level;
	int x, y;
	char Symbol;
	std::vector<Item> Inventory;
private:
	static int totalEntities;
public: 
	Entity();
	bool takeDamage(int damageTaken);
	char getChar();
	std::string getName();
	void addItem(Item item);
	std::pair<int, int> getPosition() const;
	void setPosition(int newX, int newY);
	static int getTotalEntities();
};

