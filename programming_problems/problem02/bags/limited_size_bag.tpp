#include "limited_size_bag.hpp"

//default constructor
template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
  bag_size = 0;
  T my_bag[maxsize];
}
  
// add an item to the bag
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  //require type match
  if(typeid(T) != typeid(*my_bag) || getCurrentSize() == maxsize){
    return false;
  }
  *(my_bag+bag_size) = item; 
  bag_size++;
  return true;
}

// remove an item
template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  //require type match, also can't remove from an empty bag and should contain said item
  if(typeid(T) != typeid(*my_bag) || isEmpty() || !contains(item)){
    return false;
  }
  T temp[bag_size];
  //only removing one, so index is minus 2
  int j = bag_size-2;
  bool first_instance = true;
  for(int i = bag_size-1; i >= 0; i--){
    if(my_bag[i] == item && first_instance == true){
      first_instance = false;
    } else{
      *(temp+j) = *(my_bag+i);
      j--;
    }
  }
  for(int i = 0; i < bag_size; i++){
    *(my_bag+i) = *(temp + i);
  }
  bag_size--;
  return true;
}

// check is the bag is empty
template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  return bag_size == 0;
}

// get number of items in the bag
template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return bag_size;
}

// check if item is in the bag
template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  if (isEmpty()){
    return false;
  }
  for(int i = 0; i < bag_size; i++){
    if(my_bag[i] == item){
      return true;
    }
  }
  return false;
}

// clear the bag contents
template<typename T>
void LimitedSizeBag<T>::clear(){
  memset(my_bag, 0, sizeof(*my_bag) * maxsize);
  bag_size = 0;
}

// count how many time item occurs in bag
template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t amount = 0;
  for(int i = 0; i < bag_size; i++){
    if(my_bag[i] == item){
      amount++;
    }
  }
  return amount;
};
