#pragma once
#include "Item.h"

template<class Datatype>
class InventoryNode
{
public:
	typedef InventoryNode<Datatype> Node;
private:
	Datatype fValue; //stores an item in here
	Node* fNext;
	Node* fPrevious;
	InventoryNode()
	{
		fValue = Datatype();
		fNext = &NIL;
		fPrevious = &NIL;
	}
public:
	static Node NIL;
	InventoryNode(Datatype aValue);
	void prepend(Node& aNode);
	void append(Node& aNode);
	void remove();
	Datatype getValue()
	{
		return fValue;
	}
	Node& getNext()
	{
		return *fNext;
	}
	Node& getPrevious()
	{
		return *fPrevious;
	}
};

template<class DataType>
InventoryNode<DataType> InventoryNode<DataType>::NIL;

template<class DataType>
InventoryNode<DataType>::InventoryNode(DataType aValue)
{
	fValue = aValue;
	fNext = &NIL;
	fPrevious = &NIL;
}

template<class DataType>
void InventoryNode<DataType>::prepend(Node& aNode) //pass in new node to put behind current node
{
	aNode.fNext = this; // make this current node the forward pointer of aNode
	if (fPrevious != &NIL) // make this's backward pointer aNode's
	{ // backward pointer and make previous'
		aNode.fPrevious = fPrevious; // forward pointer aNode
		fPrevious->fNext = &aNode;
	}
	fPrevious = &aNode; // this' backward pointer becomes aNode
}

template<class DataType>
void InventoryNode<DataType>::append(Node& aNode)
{
	aNode.fPrevious = this; // make this the backward pointer of aNode
	if (fNext != &NIL) // make this's forward pointer aNode's
	{ // forward pointer and make next
		aNode.fNext = fNext; // forward pointer aNode
		fNext->fPrevious = &aNode;
	}
	fNext = &aNode; // this' backward pointer becomes aNode
}

template<class DataType>
void InventoryNode<DataType>::remove()
{
	if (fNext == &NIL)
	{
		fPrevious->fNext = &NIL;
	}
	else if (fPrevious == &NIL)
	{
		fNext->fPrevious = &NIL;
	}
	else
	{
		fPrevious->fNext = fNext;
		fNext->fPrevious = fPrevious;
	}

	//delete this;
};