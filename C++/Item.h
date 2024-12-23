#pragma once
#include <string>
#include <memory>

class Item
{
protected:
	std::string Name;
	char Symbol;
public:
    Item(std::string name);
    Item();
	virtual std::string getName() const;
	char getSymbol();
};

class Weapon : public Item {
private:
    int damage;
    int enhancement;
public:
    Weapon();
    Weapon(std::string name, int damage);
    Weapon(std::string name, int damage, int enhancement);
    Weapon operator+(const Weapon& other); // Перегрузка оператора +
    Weapon& operator++(); // Префиксный ++
    Weapon operator++(int); // Постфиксный ++
    int getDamage();
    std::string getName() const override;
};