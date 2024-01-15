#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>

class Bitset{
public:

  // default constructor
  Bitset();

  // constructor with size input
  Bitset(intmax_t size);

  // consntructor with string input
  Bitset(const std::string & value);

  // default destructor to delete any dynamic memory
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // method to get the size
  intmax_t size() const;

  // method to confirm is valid or invalid
  bool good() const;

  //set value to 1 at index
  void set(intmax_t index);

  //set value to 0 at index
  void reset(intmax_t index);

  //toggle the bit
  void toggle(intmax_t index);

  //checking if 1 is present at index
  bool test(int index);

  // TODO COMMENT
  std::string asString() const;

private:
  uint8_t *array_bitset; //the bitset array
  intmax_t size_bitset; //size of bitset
  bool valid_bitset; //check if valid
};

#endif
