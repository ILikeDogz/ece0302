#include "sorted_list.hpp"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> & x)
{
  plist = x.plist; // use copy assignment to implement copy construction
}

template <typename T, typename L>
SortedList<T, L>& SortedList<T, L>::operator=(SortedList<T, L> x)
{
  plist = x.plist;
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty() const noexcept
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength() const noexcept
{
  return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T& item)
{
  size_t i = 0;
  while (i < plist.getLength() && item > plist.getEntry(i))
  {
    i++;
  }
  plist.insert(i, item);
  // TODO
}

template <typename T, typename L>
void SortedList<T, L>::remove(const T& item)
{
  if (isEmpty())
    throw std::range_error("empty list in remove");
  size_t i = 0;
  while (i != plist.getLength() && plist.getEntry(i) != item)
  {
    i++; // increment until item is found, or reach upper bound
  }
  // can reach the end and it can either contain the item or not
  if (plist.getEntry(i) != item)
  {
    throw std::range_error("item not found in list");
  }
  else
  {
    plist.remove(i);
  }
  // TODO
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position) const
{
  return plist.getEntry(position);
}

template <typename T, typename L>
long int SortedList<T, L>::getPosition(const T& newValue)
{
  size_t i = 0;
  while (i < plist.getLength())
  {
    if (plist.getEntry(i) == newValue)
    {
      // returns when it finds the item
      return i;
    }
    i++;
  }
  //no early return occured
  return -1;

}
