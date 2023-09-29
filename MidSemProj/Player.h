#pragma once
#include "Unit.h"
class Demon;

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

//player can deal damage with items or weapons in inv

class Player : public Unit
{
private:
	Item _playerItems[5]; //create new empty list for player
	Item _equippedItem;
	bool _hasEquipped;
public:
	Player();
	Player(string name, int health, int basedam);
	~Player();
	void equipItem(string name);
	bool hasEquipped();
	void unequipItem();
	Item& getEquipped();
	void useItem(string name);
	void printStatus();
	Item& getPlayerItems(int index);
	bool addItem(Item itemToAdd);
	bool removeItem(string name);
	void receiveDamage(int damage);
};

