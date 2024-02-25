#ifndef _SORT_HPP
#define _SORT_HPP
#include <iostream>
#include "linked_list.hpp"

template<typename T> LinkedList<T> sort(LinkedList<T> list)
{
	//simple implementation of selection sort. O(n^2)
	for(int end = list.getLength() - 1; end >= 0; end--){
		//after the swap occurs the end is reduced, thus end--, as the max is now at the end and doesn't need to be checked again
		int max = 0;
		for(int i = 1; i <= end; i++){
			//goes through the list, starts at 1, as max is at 0, so i = 0 can be skipped
			if(list.getEntry(i) > list.getEntry(max)){
				max = i; 
			}
		}
		if (max != end){ //if the max is currently already at the current "end", then no need to swap
			//swapping the values using a temp, to hold the data at end, as it gets overwritten, swaps last with the max
			T temp = list.getEntry(end); 
			list.setEntry(end, list.getEntry(max));
			list.setEntry(max, temp);
		}
	}
	return list;
}

#endif
