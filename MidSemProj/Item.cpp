#include "Item.h"

Item::Item()
{
	_itemName = "none";
	_damage = 0;
	_heal = 0;
}

Item::Item(string name, string desc, int damage, int heal)
{
	_itemName = name;
	_itemDesc = desc;
	_damage = damage;
	_heal = heal;
}

Item::~Item()
{
	//destructor
}

string Item::getName()
{
	return _itemName;
}

string Item::getDesc()
{
	return _itemDesc;
}

int Item::getDamage()
{
	return _damage;
}

int Item::getHeal()
{
	return _heal;
}