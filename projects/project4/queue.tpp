#include "queue.hpp"

template <typename T, typename L>
void Queue<T,L>::enqueue(const T& item)
{
  internal_list.insert(internal_list.getLength(), item);
  // TODO
}

template <typename T, typename L>
void Queue<T,L>::dequeue()
{
  if(isEmpty()){
    throw std::range_error("Error: queue is empty");
  }
  internal_list.remove(0);
  // TODO
}

template <typename T, typename L>
T Queue<T,L>::peekFront()
{
  if(isEmpty()){
    throw std::range_error("Error: queue is empty");
  }
  // TODO
  return internal_list.getEntry(0);
}

template <typename T, typename L>
bool Queue<T,L>::isEmpty() const
{
  // TODO
  return internal_list.isEmpty();
}

