#pragma once
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
using std::string;

class Item //make health packs (heal) and guns (damage)
{
private:
	string _itemName;
	string _itemDesc;
	int _damage;
	int _heal;
public:
	Item();
	Item(string name, string desc, int damage, int heal);
	~Item();
	int getDamage();
	int getHeal();
	string getName();
	string getDesc();
};

