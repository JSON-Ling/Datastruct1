#pragma once
#include "Demon.h"
#include <vector>
#include "Item.h"
#include <iostream>
#include <algorithm>


using namespace std;

typedef vector<Item> itemContainer;

//every room has its own name, description and list of items
//singly linked list of rooms
//each room has one demon in it

template<class T>

class Room
{

public:
	std::vector<Item> _itemsInRoom; //start each room with no items
	Demon _demonInRoom; //start each room with no demon
	T _roomName;
	Room* _nextRoom;
	Room() {};
	~Room() {};
	Room(const T& roomName, Room* nextRoom = (Room*)0)
	{
		_roomName = roomName;
		_nextRoom = nextRoom;
	}

	//get and set demon in room

	void addDemonToRoom(Demon demon)
	{
		_demonInRoom = demon;
	}

	Demon& getDemonInRoom()
	{
		return _demonInRoom;
	}

	//get and set items in room

	void addItemsToRoom(vector<Item> items)
	{
		_itemsInRoom = items;
	}

	vector<Item>& getItemsInRoom()
	{
		return _itemsInRoom;
	}

	bool removeItemFromRoom(string& itemName)
	{
		bool condition = false;
		for (itemContainer::iterator iter = _itemsInRoom.begin(); iter != _itemsInRoom.end(); iter++)
		{
			if (iter->getName() == itemName)
			{
				_itemsInRoom.erase(iter);
				condition = true;
				break;
			}
		}
		return condition;
	}

	void setNextRoom(Room* next)
	{
		_nextRoom = next;
	}
};

