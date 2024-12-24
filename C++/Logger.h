#pragma once
#include <string>
#include <vector>

class Game;

class Logger
{
private:
	std::vector<std::string> logs;
public:
	Logger();
	void addLine(std::string);
	std::string getLastEvents();
};
