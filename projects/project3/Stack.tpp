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
	//no destructor needs to be called, due to smart pointers automatically deallocating
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
	std::shared_ptr<Node<ItemType>> nextNodePtr = std::make_shared<Node<ItemType>>(newItem, headPtr); // alternate code
	headPtr = nextNodePtr;          // New node is now first node
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
	//move to the next, the old is automatically deleted because of smart pointer
	headPtr = std::move(headPtr->getNext()); 
	currentSize--;
    return true;
}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	//continue to pop, until headPtr is null
	while(headPtr) {
		//moves headPtr until it is nullptr
     	headPtr = std::move(headPtr->getNext());
    }
	currentSize = 0;
}  // end clear

