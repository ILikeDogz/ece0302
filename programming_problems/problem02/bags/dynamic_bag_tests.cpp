#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

int testing_array[10] = {1,2,-2,3,3,4,5,4,4,4};
int testing_array_two[10] = {0,0,-300,7,0,0,0,0,9,10};
// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Checking that add works as intended", "[DynamicBag]"){
  DynamicBag<int> b;
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
    b.contains(testing_array[i]);
  }
  REQUIRE_FALSE(b.contains(7));
  REQUIRE(b.getFrequencyOf(4) == 4);
  REQUIRE(b.add(3));
}

TEST_CASE("Checking that remove fails on an empty bag", "[DynamicBag]"){
  DynamicBag<int> b;
  REQUIRE_FALSE(b.remove(0));
}

TEST_CASE("Checking that remove works as intended", "[DynamicBag]"){
  DynamicBag<int> b;
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
  }
  REQUIRE(b.remove(1));
  REQUIRE_FALSE(b.contains(1));
  REQUIRE(b.getCurrentSize() == 9);
  b.remove(4);
  REQUIRE_FALSE(b.getFrequencyOf(4) == 4);
  REQUIRE(b.getFrequencyOf(4) == 3);
  b.remove(3);
  REQUIRE_FALSE(b.getFrequencyOf(3) == 2);
  REQUIRE(b.getFrequencyOf(3) == 1);
  b.remove(5);
  REQUIRE(b.getCurrentSize() == 6);
  REQUIRE(b.getFrequencyOf(5) == 0);
  REQUIRE_FALSE(b.remove(6));
}

TEST_CASE("Checking that getCurrentSize works as intended", "[DynamicBag]"){
  DynamicBag<int> b;
  REQUIRE(b.isEmpty());
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
    REQUIRE(b.getCurrentSize() == i+1);
  }
  REQUIRE_FALSE(b.isEmpty());
  REQUIRE(b.getCurrentSize() == 10);
}

TEST_CASE("Checking that clear and is empty works as intended", "[DynamicBag]"){
  DynamicBag<int> b;
  REQUIRE(b.isEmpty());
  b.clear();
  REQUIRE(b.isEmpty());
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
  }
  REQUIRE_FALSE(b.isEmpty());
  b.clear();
  REQUIRE(b.isEmpty());
}

TEST_CASE("Checking that swap works as intended", "[DynamicBag]"){
  DynamicBag<int> b;
  DynamicBag<int> c;
  REQUIRE(b.isEmpty());
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
    c.add(testing_array_two[i]);
    REQUIRE_FALSE(b.contains(testing_array_two[i]));
    REQUIRE_FALSE(c.contains(testing_array[i]));
  }
  b.swap(c);
  for(int i = 0; i < 10; i++){
    REQUIRE(b.contains(testing_array_two[i]));
    REQUIRE(c.contains(testing_array[i]));
  }
}

TEST_CASE("Checking that copy constructor works as intended", "[DynamicBag]"){
  DynamicBag<int> b;
  REQUIRE(b.isEmpty());
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
  }
  DynamicBag<int> c(b);
  for(int i = 0; i < 10; i++){
    REQUIRE(c.contains(testing_array[i]));
  }
  REQUIRE(c.getCurrentSize() == b.getCurrentSize());
}

TEST_CASE("Checking that = works as intended", "[DynamicBag]"){
  DynamicBag<int> b;
  DynamicBag<int> c;
  REQUIRE(b.isEmpty());
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
    REQUIRE_FALSE(c.contains(testing_array[i]));
  }
  c = b;
  for(int i = 0; i < 10; i++){
    REQUIRE(c.contains(testing_array[i]));
  }
  REQUIRE(c.getCurrentSize() == b.getCurrentSize());
  DynamicBag<int> d = c;
  for(int i = 0; i < 10; i++){
    REQUIRE(d.contains(testing_array[i]));
  }
  REQUIRE(d.getCurrentSize() == b.getCurrentSize());
}

TEST_CASE("Calling all public members", "[DynamicBag]"){
  DynamicBag<int> b;
  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}
