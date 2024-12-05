#include "Entity.h"

bool Entity::takeDamage(int damageTaken) {
	damageTaken -= Defense;
	if (damageTaken > 0) {
		Health -= damageTaken;
		return true;
	}
	return false;
}

char Entity::getChar() {
	return Symbol;
}