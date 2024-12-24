#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Entity
{
protected:
	std::string Name;
	int Health, Defense, Attack, Level;
	int x, y;
	char Symbol;
	std::vector<std::shared_ptr<Item>> Inventory;
private:
	static int totalEntities;
public: 
	Entity();
	Entity& takeDamage(int damageTaken);
	char getChar();
	std::string getName();
	int getHealth();
	void addItem(std::shared_ptr<Item> item);
	std::pair<int, int> getPosition() const;
	void setPosition(int newX, int newY);
	static int getTotalEntities();
	std::vector<std::shared_ptr<Item>> getInventory();
};

