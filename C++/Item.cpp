#include "Item.h"

Item::Item(std::string name) {
	Name = name;
	Symbol = Name[0];
}

std::string Item::getName() {
	return Name;
}

char Item::getSymbol() {
	return Symbol;
}
