#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "Item.h"
#include "Inventory.h"

class Entity
{
protected:
	std::string Name;
	int Health, Defense, Attack, Level;
	int x, y;
	char Symbol;
	virtual void onLevelUp() = 0;
private:
	static int totalEntities;
public: 
	Inventory<std::shared_ptr<Item>> inventory;

	Entity();
	Entity(std::string Name, int Health, int Defense, int Attack, int Level, char Symbol);
	Entity& takeDamage(int damageTaken);
	Entity& operator=(const Entity& other);
	friend std::ostream& operator<<(std::ostream& os, const Entity& entity);
	char getChar();
	std::string getName();
	int getHealth();
	std::pair<int, int> getPosition() const;
	void setPosition(int newX, int newY);
	static int getTotalEntities();
};

