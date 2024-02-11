#include "linked_list.hpp"
template <typename T>
LinkedList<T>::LinkedList()
{
  head = nullptr;
  // TODO
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  Node<T> *position = head;
  Node<T> *next = nullptr;

  while (position != nullptr)
  { // traverse the list and delete the list
    next = position->getNext();
    delete position;
    position = next;
  }
  // TODO
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &x)
{
  head = nullptr;
  if (x.head != nullptr)
  {
    head = nullptr;
    Node<T> *x_position = x.head;
    Node<T> *main_position = nullptr;

    while (x_position != nullptr)
    {
      // Create a node, holding the item of x, at the current position
      Node<T> *item_node = new Node<T>(x_position->getItem());

      if (head == nullptr)
      {
        // Empty case, set head to the node of the first item of x

        head = item_node;
        main_position = head;
      }
      else
      {
        // If not the first item, link the new node to the next position
        main_position->setNext(item_node);
        main_position = main_position->getNext();
      }
      x_position = x_position->getNext(); // Move to the next position in x
    }
  }
  // TODO
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  // TODO
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList &x)
{
  std::swap(head, x.head);
  // TODO
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  if (head == nullptr)
  {
    return true;
  }
  // TODO
  return false;
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  size_t list_size = 0;
  Node<T> *main_position = head;
  while (main_position != nullptr)
  {
    main_position = main_position->getNext(); // traverse the list
    list_size++;
  }
  // TODO
  return list_size;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T &item)
{
  if (position < 0 || position > getLength())
  {
    return false;
  }

  Node<T> *item_node = new Node<T>(item);

  if (isEmpty())
  {
    // empty case, set head to node of first item of x
    head = item_node;
    return true;
  }

  if (position == 0)
  {
    // set current head to after item_node, head = item_node
    item_node->setNext(head);
    head = item_node;
    return true;
  }

  Node<T> *main_position = head;
  Node<T> *previous = nullptr;
  size_t i = 0;
  while (main_position != nullptr && i < position)
  { // traverse the list until we reach the position
    previous = main_position;
    main_position = main_position->getNext();
    i++;
  }
  // connect previous to item node, and reconnect it to the rest of the list by connecting item_node to main_position
  previous->setNext(item_node);
  item_node->setNext(main_position);

  // TODO
  return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  if (position < 0 || position >= getLength())
  { // accounts for length = 0
    return false;
  }

  Node<T> *main_position = head;
  Node<T> *previous = nullptr;
  if (position == 0)
  {
    // delete main position, after setting the head to position after
    head = main_position->getNext();
    delete main_position;
    return true;
  }

  size_t i = 0;
  while (main_position != nullptr && i < position)
  { // traverse the list until we reach the position
    previous = main_position;
    main_position = main_position->getNext();
    i++;
  }

  previous->setNext(main_position->getNext());
  // imagine a list like previous, main_position, main_next, in this list main_position is replaced by main_next, and then deleted

  delete main_position;
  // TODO
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  Node<T> *position = head;
  Node<T> *next = nullptr;

  while (position != nullptr)
  { // traverse the list and delete the list
    next = position->getNext();
    delete position;
    position = next;
  }
  head = nullptr;
  // TODO
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  if (position < 0 || position >= getLength())
  {
    return T();
  }

  Node<T> *main_position = head;
  size_t i = 0;
  while (main_position != nullptr && i < position)
  {
    main_position = main_position->getNext(); // traverse the list
    i++;
  }
  return main_position->getItem();
  // TODO
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T &newValue)
{
  if (position < 0 || position >= getLength())
  {
    return;
  }

  Node<T> *main_position = head;
  size_t i = 0;
  while (main_position != nullptr && i < position)
  {
    main_position = main_position->getNext(); // traverse the list
    i++;
  }
  main_position->setItem(newValue);
  // TODO
}
