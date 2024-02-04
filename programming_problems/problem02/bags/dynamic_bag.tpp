#include "dynamic_bag.hpp"
#include <cstring>

//default constructor
template<typename T>
DynamicBag<T>::DynamicBag() {
  bag_size = 0;
  my_bag = (T*) malloc(bag_size*sizeof(T));
}
  

//copy constructor
template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x){
  bag_size = x.bag_size;
  my_bag = (T*) malloc(bag_size*sizeof(T));
  std::memcpy(my_bag, x.my_bag, bag_size * sizeof(T));
}

//destructor  
template<typename T>
DynamicBag<T>::~DynamicBag(){
  free(my_bag);
}
  
//copy assignment
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> &x)
{  
  if (this != &x) {
  bag_size = x.bag_size;

  //reallocate the size, as bag_size could be different
  my_bag = (T*) realloc(my_bag, bag_size * sizeof(T));

  std::memcpy(my_bag, x.my_bag, bag_size * sizeof(T));
  }
  return *this;
}

// swap for copy swap idiom
template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x){
  //bag sizes may be different, so after size is swapped, the memory is reallocated for the new size
  T temp_size = bag_size;
  T temp[bag_size];
  std::memcpy(temp, my_bag, bag_size * sizeof(T));

  bag_size = x.bag_size;
  my_bag = (T*) realloc(my_bag, bag_size * sizeof(T));
  std::memcpy(my_bag, x.my_bag, bag_size * sizeof(T));

  x.bag_size = temp_size;
  x.my_bag = (T*) realloc(x.my_bag, x.bag_size * sizeof(T));
  std::memcpy(x.my_bag, temp, x.bag_size * sizeof(T));
}

// add an item to the bag
template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  //require type match
  if(typeid(T) != typeid(*my_bag)){
    return false;
  }
  my_bag = (T*) realloc(my_bag, ++bag_size * sizeof(T));
  *(my_bag+bag_size-1) = item; 
  return true;
}

// remove an item
template<typename T>
bool DynamicBag<T>::remove(const T& item)
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
      *(temp+j) = *(my_bag+(i));
      j--;
    }
  }
  my_bag = (T*) realloc(my_bag, --bag_size * sizeof(T));
  std::memcpy(my_bag, temp, bag_size * sizeof(T));
  return true;
}

// check is the bag is empty
template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  return bag_size == 0;
}

// get number of items in the bag
template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return bag_size;
}

// check if item is in the bag
template<typename T>
bool DynamicBag<T>::contains(const T& item) const
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
void DynamicBag<T>::clear(){
  free(my_bag);
  bag_size = 0;
  my_bag = (T*) malloc(bag_size*sizeof(T));
}

// count how many time item occurs in bag
template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t amount = 0;
  for(int i = 0; i < bag_size; i++){
    if(my_bag[i] == item){
      amount++;
    }
  }
  return amount;
};
