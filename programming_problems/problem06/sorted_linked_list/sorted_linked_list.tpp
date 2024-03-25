#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList() : LinkedList<T>()
{
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(LinkedList<T> unsorted_list)
{
  LinkedList<T> my_temp_list = unsorted_list;
  for (int end = my_temp_list.getLength() - 1; end >= 0; end--)
  {
    // after the swap occurs the end is reduced, thus end--, as the max is now at the end and doesn't need to be checked again
    int max = 0;
    for (int i = 1; i <= end; i++)
    {
      // goes through the list, starts at 1, as max is at 0, so i = 0 can be skipped
      if (my_temp_list.getEntry(i) > my_temp_list.getEntry(max))
      {
        max = i;
      }
    }
    if (max != end)
    { // if the max is currently already at the current "end", then no need to swap
      // swapping the values using a temp, to hold the data at end, as it gets overwritten, swaps last with the max
      T temp = my_temp_list.getEntry(end);
      my_temp_list.setEntry(end, my_temp_list.getEntry(max));
      my_temp_list.setEntry(max, temp);
    }
  }
  //swap the temp list, so the original list is left as it was, and the list in the sorted list is sorted
  LinkedList<T>::swap(my_temp_list);
  // TODO
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> &x) : LinkedList<T>(x)
{
  //Sorted contains none of its own private variables, so it just needs to take the LinkedList
}

template <typename T>
SortedLinkedList<T> &SortedLinkedList<T>::operator=(SortedLinkedList<T> x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty() const noexcept
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength() const noexcept
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T &item)
{
  size_t i = 0;
  while (i < getLength() && item > getEntry(i))
  {
    i++;
  }
  LinkedList<T>::insert(i, item);
  // TODO
}

template <typename T>
void SortedLinkedList<T>::remove(const T &item)
{
  if (isEmpty())
    throw std::range_error("empty list in remove");
  size_t i = 0;
  while (i != getLength() && getEntry(i) != item)
  {
    i++; // increment until item is found, or reach upper bound
  }
  // can reach the end and it can either contain the item or not
  if (getEntry(i) != item)
  {
    throw std::range_error("item not found in list");
  }
  else
  {
    LinkedList<T>::remove(i);
  }
  // TODO
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  if (isEmpty())
    throw std::range_error("empty list in remove");
  // remove already searches for position
  LinkedList<T>::remove(position);
  // TODO
}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) const
{
  return LinkedList<T>::getEntry(position);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T &item)
{
  size_t i = 0;
  while (i < getLength())
  {
    if (getEntry(i) == item)
    {
      // returns when it finds the item
      return i;
    }
    i++;
  }
  //no early return occured
  return -1;

  // TODO
}
