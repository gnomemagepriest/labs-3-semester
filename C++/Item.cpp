#include "Item.h"

Item::Item(std::string name) {
	Name = name;
	Symbol = Name[0];
}

Item::Item() {
    Name = "";
    Symbol = 0;
}

std::string Item::getName() const  {
	return Name;
}

char Item::getSymbol() {
	return Symbol;
}

Weapon::Weapon(std::string name, int damage) : Item(name), damage(damage) {
    enhancement = 0;
}

Weapon::Weapon(std::string name, int damage, int enhancement) : Item(name), damage(damage), enhancement(enhancement) {}

Weapon::Weapon() {
    Name = "";
    damage = 0;
    enhancement = 0;
}

Weapon Weapon::operator+(const Weapon& other) {
    if (this->Name == other.Name) {
        return Weapon(this->Name, this->damage, this->enhancement + 1);
    }
    return *this;
}

Weapon& Weapon::operator++() {
    this->enhancement++;
    return *this;
}

Weapon Weapon::operator++(int) {
    Weapon temp = *this;
    this->enhancement++;
    return temp;
}

int Weapon::getDamage() {
    return damage;
}

std::string Weapon::getName() const {
    return Name + " +" + std::to_string(enhancement);
}
