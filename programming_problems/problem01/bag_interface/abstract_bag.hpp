#ifndef _ABSTRACT_BAG_HPP_
#define _ABSTRACT_BAG_HPP_

#include <cstdlib>

//TODO
template<typename T> class AbstractBag{
public:

    //returns size variable
  virtual std::size_t getCurrentSize() const = 0;

    //compares size to 0, and checks whether condition is true or false
  virtual bool isEmpty() const = 0;

    //checks whether bag is full or not, and if not full, adds entry to the bag
  virtual bool add(const T& entry) = 0;

  virtual bool remove(const T& entry) = 0;

  virtual void clear() = 0;

  virtual std::size_t getFrequencyOf(const T& entry) const = 0;

  virtual bool contains(const T& entry) const = 0;
  
};

#endif