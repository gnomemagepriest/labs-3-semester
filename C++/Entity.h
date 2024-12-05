#pragma once
#include <string>
#include "Logger.h"

class Entity
{
protected:
	std::string Name;
	int Health, Defense, Level;
	int x, y;
	char Symbol;
	bool takeDamage(int damageTaken);
public: 
	virtual void move(int dx, int dy) const = 0;
	virtual void makeTurn(Logger& logger) const = 0;
	char getChar();
};

