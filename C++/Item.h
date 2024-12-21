#pragma once
#include <string>

class Item
{
protected:
	std::string Name;
	char Symbol;
public:
    Item(std::string name);
	std::string getName();
	char getSymbol();
};

