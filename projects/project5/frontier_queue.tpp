#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop()
{

  // TODO
  if (queue.empty())
  {
    throw std::out_of_range("Cannot pop from an empty frontier queue.");
  }

  // implement this the same way we implemented pop in the heap lecture. Compare using getFCost

  // get root
  State<T> smallest = queue.front();

  // swap root with end
  std::swap(queue.front(), queue.back());

  // remove root, now at the back
  queue.pop_back();

  // heapify into a max heap
  std::size_t index = 0;
  std::size_t heap_size = queue.size();
  while (true)
  {
    //cool indexing for binary trees
    std::size_t left_child = 2 * index + 1;
    std::size_t right_child = 2 * index + 2;
    std::size_t current_child = index;

    // check if left or right is smaller than current child
    if (left_child < heap_size && queue[left_child].getFCost() < queue[current_child].getFCost())
    {
      current_child = left_child;
    }
    if (right_child < heap_size && queue[right_child].getFCost() < queue[current_child].getFCost())
    {
      current_child = right_child;
    }

    // if neither child is smaller than current child,
    if (current_child == index)
    {
      break;
    }
    else
    {
      std::swap(queue[index], queue[current_child]);
      index = current_child;
      ;
    }
  }

  // needs return statement
  return smallest;
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur)
{

  // TODO

  // implement this the same way we implemented push in the heap lecture.

  // new state
  State<T> my_state(p, cost, heur);

  // add to empty spot
  queue.push_back(my_state);

  // heapify into a max heap
  std::size_t index = 0;
  std::size_t heap_size = queue.size();
  while (true)
  {
    //cool indexing for binary trees
    std::size_t left_child = 2 * index + 1;
    std::size_t right_child = 2 * index + 2;
    std::size_t current_child = index;

    // check if left or right is smaller than current child
    if (left_child < heap_size && queue[left_child].getFCost() < queue[current_child].getFCost())
    {
      current_child = left_child;
    }
    if (right_child < heap_size && queue[right_child].getFCost() < queue[current_child].getFCost())
    {
      current_child = right_child;
    }

    // if neither child is smaller than current child,
    if (current_child == index)
    {
      break;
    }
    else
    {
      std::swap(queue[index], queue[current_child]);
      index = current_child;
      ;
    }
  }
}

template <typename T>
bool frontier_queue<T>::empty()
{

  // TODO

  return queue.empty();
}

template <typename T>
bool frontier_queue<T>::contains(const T &p)
{

  // iterate through until item found
  for (State<T> my_item : queue)
    if (my_item.getValue() == p)
    {
      return true;
    }
  // item not found
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{
  for (std::size_t i = 0; i < queue.size(); i++)
  {
    if (queue[i].getValue() == p)
    {
      // update the path cost
      if (cost < queue[i].getPathCost())
      {
        queue[i].updatePathCost(cost);

        // heapify into a max heap
        std::size_t index = 0;
        std::size_t heap_size = queue.size();
        while (true)
        {
          //cool indexing for binary trees
          std::size_t left_child = 2 * index + 1;
          std::size_t right_child = 2 * index + 2;
          std::size_t current_child = index;

          // check if left or right is smaller than current child
          if (left_child < heap_size && queue[left_child].getFCost() < queue[current_child].getFCost())
          {
            current_child = left_child;
          }
          if (right_child < heap_size && queue[right_child].getFCost() < queue[current_child].getFCost())
          {
            current_child = right_child;
          }

          // if neither child is smaller than current child,
          if (current_child == index)
          {
            break;
          }
          else
          {
            std::swap(queue[index], queue[current_child]);
            index = current_child;
            ;
          }
        }
      }
    }
  }
  // TODO
}
