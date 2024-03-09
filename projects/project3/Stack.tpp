//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template<class ItemType>
Stack<ItemType>::Stack() 
{
	currentSize = 0;
	headPtr = nullptr;
}  // end default constructor

// TODO: Implement the destructor here
template<class ItemType>
Stack<ItemType>::~Stack()
{
	Node<ItemType> *position = headPtr;
	Node<ItemType> *next = nullptr;

  	while (position != nullptr)
  		{ // traverse the links and delete
    	next = position->getNext();
    	delete position;
    	position = next;
  	}
}  // end destructor

// TODO: Implement the isEmpty method here
template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return currentSize == 0;
}  // end isEmpty

// TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
}  // end size

// TODO: Implement the push method here
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType> *item_node = new Node<ItemType>(newItem, headPtr);
	headPtr = item_node;
	currentSize++;
	return true;
}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	if(currentSize <= 0 || headPtr == nullptr){
		throw std::logic_error("Empty Stack");
	}
	return headPtr->getItem();
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	if(currentSize <= 0 || headPtr == nullptr){
		return false;
	}
	Node<ItemType> *temp = headPtr;
	headPtr = headPtr->getNext();
	delete temp;
	currentSize--;
	return false;
}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	Node<ItemType> *position = headPtr;
	Node<ItemType> *next = nullptr;

  	while (position != nullptr)
  		{ // traverse the links and delete
    	next = position->getNext();
    	delete position;
    	position = next;
  	}
	currentSize = 0;
	headPtr = nullptr;
}  // end clear

