#include "RoomIterator.h"
using namespace std;

template<class T>
RoomIterator<T>::RoomIterator(Room<T>* room)
{
	_room = room; 
}

template<class T>
Room<T>& RoomIterator<T>::operator*()
{
	return *this->_room;
}

template<class T>
RoomIterator<T>& RoomIterator<T>::operator++() //prefix
{
	if (_room != (Room<T>*)0)
	{
		_room = _room->_nextRoom;
	}
	return *this;
}

template<class T>
RoomIterator<T> RoomIterator<T>::operator++(int) //postfix
{
	RoomIterator<T> temp = *this;
	if (_room != (Room<T>*)0)
	{
		_room = _room->_nextRoom;
	}
	return temp;
}

template<class T>
bool RoomIterator<T>::operator==(const Iterator& aOther)
{
	return (_room == aOther._room);
}

template<class T>
bool RoomIterator<T>::operator!=(const Iterator& aOther)
{
	return !(*this == aOther);
}

template<class T>
RoomIterator<T> RoomIterator<T>::end()
{
	RoomIterator<T> temp = *this;
	while (1)
	{
		if (temp._room->_nextRoom != (Room<T>*)0)
		{
			temp._room = temp._room->_nextRoom;
		}
		else
		{
			return temp;
		}
	}
}