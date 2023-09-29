#pragma once
#include "Room.h"

template<class T>
class RoomIterator
{
private:
	Room<T>* _room;
public:
	typedef RoomIterator<T> Iterator;
	RoomIterator(Room<T>* room);
	Room<T>& operator*(); //dereferencer
	Iterator& operator++(); //prefix
	Iterator operator++(int); //postfix
	bool operator==(const Iterator& aOther);
	bool operator!=(const Iterator& aOther);
	Iterator end();
};

