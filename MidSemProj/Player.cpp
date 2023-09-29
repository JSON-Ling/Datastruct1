#include "Player.h"
#include "Demon.h"

Player::Player():Unit()
{
	_hasEquipped = false;
	//creates empty inv
}

Player::Player(string name, int health, int basedam) : Unit(name, health, basedam)
{
	_hasEquipped = false;
	//creates empty inv
}

Player::~Player()
{

}

bool Player::hasEquipped()
{
	return _hasEquipped;
}

void Player::equipItem(string name)
{
	string equipOutput = "You don't have that item in your inventory to equip or it is not equippable.";
	//search for item name in player's inventory, then add it to equipped items
	for (int i = 0; i < 5; i++)
	{
		if (_playerItems[i].getName() == name && _playerItems[i].getDamage() != 0)
		{
			_equippedItem = _playerItems[i];
			_hasEquipped = true;
			equipOutput = _equippedItem.getName() + " has been equipped.";
			break;
		}
	}
	cout << equipOutput << endl;
}

void Player::unequipItem()
{
	if (_equippedItem.getName() != "none")
	{
		cout << _equippedItem.getName() << " has been unequipped." << endl;
		_hasEquipped = false;
		_equippedItem = Item();
	}
	else
	{
		cout << "You don't have an item to unequip at the moment. " << endl;
	}
}

Item& Player::getEquipped()
{
	return _equippedItem;
}

void Player::useItem(string name)
{
	string output = "Item specified cannot be used.";
	for (int i = 0; i < 5; i++)
	{
		if (_playerItems[i].getName() == name && _playerItems[i].getHeal() != 0)
		{
			setHealth(_playerItems[i].getHeal() + getHealth());
			output = "You healed yourself with: " + _playerItems[i].getName();
			_playerItems[i] = Item(); //replace consumed item with empty item
			break;
		}
	}
	cout << output << endl;
}

void Player::receiveDamage(int damage)
{
	int newHealth = getHealth() - damage;
	if (newHealth <= 0)
	{
		setHealth(0);
	}
	else
	{
		setHealth(newHealth);
	}
}

void Player::printStatus()
{
	std::cout << "Health of Player is: " << getHealth() << endl;
	std::cout << "Name of Player is: " << getName() << endl;
	std::cout << "Base damage of Player is: " << getBaseDamage() << endl;
	std::cout << "Currently equipped item is: " << _equippedItem.getName() << endl;
	std::cout << "Currently equipped item damage is: " << _equippedItem.getDamage() << endl;
}

Item& Player::getPlayerItems(int index)
{
	return _playerItems[index];
}

bool Player::addItem(Item itemToAdd)
{
	bool condition = false;
	for (int i = 0; i < 5; i++)
	{
		if (_playerItems[i].getName() == "none")
		{
			_playerItems[i] = itemToAdd;
			condition = true;
			break;
		}
	}
	return condition;
}

bool Player::removeItem(string name) //remove item from players inventory and if item exists in equipped slot, remove it too
{
	string output = "Item not found";
	bool condition = false;
	for (int i = 0; i < 5; i++)
	{
		if (_playerItems[i].getName() == name)
		{
			if (_equippedItem.getName() == name)
			{
				_equippedItem = Item();
				_hasEquipped = false;
			}
			output = _playerItems[i].getName() + " has been removed from your inventory forever";
			_playerItems[i] = Item();
			condition = true;
			break;
		}
	}
	cout << output << endl;
	return condition;
}

