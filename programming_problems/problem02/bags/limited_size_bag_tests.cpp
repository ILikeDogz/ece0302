#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"


int testing_array[10] = {1,2,-2,3,3,4,5,4,4,4};
int testing_array_two[10] = {0,0,-300,7,0,0,0,0,9,10};

// force template expansion for ints
template class LimitedSizeBag<int>;


TEST_CASE("Checking that add works as intended", "[DynamicBag]"){
  LimitedSizeBag<int> b;
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
    b.contains(testing_array[i]);
  }
  REQUIRE_FALSE(b.contains(7));
  REQUIRE(b.getFrequencyOf(4) == 4);
}

TEST_CASE("Checking that remove fails on an empty bag", "[DynamicBag]"){
  LimitedSizeBag<int> b;
  REQUIRE_FALSE(b.remove(0));
}

TEST_CASE("Checking that add fails on a full bag", "[DynamicBag]"){
  LimitedSizeBag<int> b;
  for(int i = 0; i < 100; i++){
    b.add(i);
  }
  REQUIRE(b.getCurrentSize() == 100);
  REQUIRE_FALSE(b.add(0));
}

TEST_CASE("Checking that remove works as intended", "[DynamicBag]"){
  LimitedSizeBag<int> b;
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
  LimitedSizeBag<int> b;
  REQUIRE(b.isEmpty());
  for(int i = 0; i < 10; i++){
    b.add(testing_array[i]);
    REQUIRE(b.getCurrentSize() == i+1);
  }
  REQUIRE_FALSE(b.isEmpty());
  REQUIRE(b.getCurrentSize() == 10);
}

TEST_CASE("Checking that clear and is empty works as intended", "[DynamicBag]"){
  LimitedSizeBag<int> b;
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


TEST_CASE("Calling all public members", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);

}
