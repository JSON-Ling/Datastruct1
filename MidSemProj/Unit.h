#pragma once
#include "Item.h"
#include <iostream>
#include <string>
using std::string;

class Unit //make demons and the player out of this
{
private:
	int _health;
	int _baseDamage;
	string _name;
public:
	Unit();
	Unit(string name, int health, int basedam);
	~Unit();
	int getHealth();
	void setHealth(int health);
	string getName();
	void setName(string name);
	int getBaseDamage();
	bool isDead();
	virtual void printStatus();
};

