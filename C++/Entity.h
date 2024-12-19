#pragma once
#include <string>

class Logger;
class Map;
class Game;

class Entity
{
protected:
	std::string Name;
	int Health, Defense, Level;
	char Symbol;
	bool takeDamage(int damageTaken);
public: 
	//virtual void move(Map* map, int dx, int dy) = 0;
	//virtual void makeTurn(Map* map, Logger& logger) = 0;
	char getChar();
	int x, y;
};

