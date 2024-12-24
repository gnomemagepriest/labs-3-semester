#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "Item.h"

class Entity
{
protected:
	std::string Name;
	int Health, Defense, Attack, Level;
	int x, y;
	char Symbol;
	std::vector<std::shared_ptr<Item>> Inventory;
	virtual void onLevelUp() = 0;
private:
	static int totalEntities;
public: 
	Entity();
	Entity& takeDamage(int damageTaken);
	Entity& operator=(const Entity& other);
	friend std::ostream& operator<<(std::ostream& os, const Entity& entity);
	char getChar();
	std::string getName();
	int getHealth();
	void addItem(std::shared_ptr<Item> item);
	std::pair<int, int> getPosition() const;
	void setPosition(int newX, int newY);
	static int getTotalEntities();
	std::vector<std::shared_ptr<Item>> getInventory();
};

