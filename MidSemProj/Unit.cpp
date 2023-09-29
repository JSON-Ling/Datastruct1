#include "Unit.h"

Unit::Unit()
{
	_health = 1;
	_name = "none";
	_baseDamage = 0;
}

Unit::Unit(string name, int health, int basedam)
{
	_health = health;
	_name = name;
	_baseDamage = basedam;
}

Unit::~Unit()
{

}

bool Unit::isDead()
{
	bool condition = false;
	if(_health == 0)
	{
		condition = true;
	}
	return condition;
}

int Unit::getHealth()
{
	return _health;
}

void Unit::setHealth(int health)
{
	_health = health;
}

string Unit::getName()
{
	return _name;
}

void Unit::setName(string name)
{
	_name = name;
}

int Unit::getBaseDamage()
{
	return _baseDamage;
}

void Unit::printStatus()
{
	std::cout << "Health of Unit is: " << _health;
	std::cout << "Name of Unit is: " << _name;
	std::cout << "Base damage of Unit is: " << _baseDamage;
}
