#ifndef _SORT_HPP
#define _SORT_HPP
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "linked_list.hpp"

template <typename T>
bool isSorted(LinkedList<T> &list)
{
	// goes through the list, ensuring the follwing entry is greater than prior, or fails
	for (int i = 0; i < list.getLength() - 1; ++i)
	{
		if (list.getEntry(i) > list.getEntry(i + 1))
		{
			return false;
		}
	}
	return true;
}

template <typename T>
void shuffleLinkedList(LinkedList<T> &list)
{
	//seeded with time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	size_t length = list.getLength();
	if (length <= 1)
	{
		return;
	}
	for (size_t i = length - 1; i > 0; --i)
	{
		size_t j = std::rand() % (i + 1);
		// sets j to a random number, and swaps i and j then
		T temp = list.getEntry(j);
		list.setEntry(j, list.getEntry(i));
		list.setEntry(i, temp);
	}
}

template <typename T>
LinkedList<T> sort(LinkedList<T> list)
{
	//seeded with time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// this is bogo sort, randomize until it is sorted
	while (!isSorted(list))
	{
		shuffleLinkedList(list);
	}
	// //simple implementation of selection sort. O(n^2)
	// for(int end = list.getLength() - 1; end >= 0; end--){
	// 	//after the swap occurs the end is reduced, thus end--, as the max is now at the end and doesn't need to be checked again
	// 	int max = 0;
	// 	for(int i = 1; i <= end; i++){
	// 		//goes through the list, starts at 1, as max is at 0, so i = 0 can be skipped
	// 		if(list.getEntry(i) > list.getEntry(max)){
	// 			max = i;
	// 		}
	// 	}
	// 	if (max != end){ //if the max is currently already at the current "end", then no need to swap
	// 		//swapping the values using a temp, to hold the data at end, as it gets overwritten, swaps last with the max
	// 		T temp = list.getEntry(end);
	// 		list.setEntry(end, list.getEntry(max));
	// 		list.setEntry(max, temp);
	// 	}
	// }
	return list;
}

#endif
