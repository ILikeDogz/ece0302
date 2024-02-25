#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"
#include "sort.hpp"



// write your test cases here
TEST_CASE("Test case", "sorting"){

  LinkedList<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  LinkedList<int> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 4);
  REQUIRE(sorted.getEntry(1) == 10);
  REQUIRE(sorted.getEntry(2) == 11);
  REQUIRE(sorted.getEntry(3) == 25);
  REQUIRE(sorted.getEntry(4) == 100);
  
}


TEST_CASE("Test case: Pre-Sorted", "sorting"){

  LinkedList<int> lst;

  for(int i = 0; i <= 100; i ++){
    lst.insert(i,i); //creates a list already sorted in ascending order
  }

  LinkedList<int> sorted = sort(lst);

  for(int i = 0; i <= 100; i++){
    REQUIRE(sorted.getEntry(i) == i);
    REQUIRE(sorted.getEntry(i) == lst.getEntry(i));
  }  
}


TEST_CASE("Test case: Descending to Ascending", "sorting"){

  LinkedList<int> lst;

  for(int i = 100; i >= 0; i--){
    lst.insert(100-i,i); //creates a list in descending order
  }

  LinkedList<int> sorted = sort(lst);

  for(int i = 0; i <= 100; i++){
    REQUIRE(sorted.getEntry(i) == i);
  }  
}


TEST_CASE("Test case: Descending to Ascending, Double", "sorting"){

  LinkedList<double> lst;

  for(double i = 100; i >= 0; i--){
    lst.insert(100-i,i/2); //creates a list in descending order
  }

  LinkedList<double> sorted = sort(lst);

  for(double i = 0; i <= 100; i++){
    REQUIRE(sorted.getEntry(i) == i/2);
  }  
}

TEST_CASE("Test case: all equal", "sorting"){

  LinkedList<int> lst;

  for(int i = 0; i <= 100; i ++){
    lst.insert(i, 1); //creates a list of the same value
  }

  LinkedList<int> sorted = sort(lst);

  for(int i = 0; i <= 100; i++){
    REQUIRE(sorted.getEntry(i) == 1);
    REQUIRE(sorted.getEntry(i) == lst.getEntry(i));
  }  
}

TEST_CASE("Test case: Sorting Multiple Times", "sorting"){

  LinkedList<int> lst;

  for(int i = 100; i >= 0; i--){
    lst.insert(100-i,i); //creates a list in descending order
  }

  LinkedList<int> sorted = sort(lst);

  for(int i = 0; i <= 100; i++){
    REQUIRE(sorted.getEntry(i) == i);
  }  

  for(int i = 200; i >= 101; i--){
    lst.insert(200-i,i); //adds to the list in descending order
  }

  LinkedList<int> sorted2 = sort(lst);

  for(int i = 0; i <= 100; i++){
    REQUIRE(sorted.getEntry(i) == i);
    REQUIRE(sorted.getEntry(i) == sorted2.getEntry(i));
  }  
  for(int i = 101; i <= 200; i++){
    REQUIRE(sorted2.getEntry(i) == i);
  }  
}

TEST_CASE("Test case: Character", "sorting"){

  LinkedList<char> lst;

  lst.insert(0, 'c');

  lst.insert(1, 'a');

  lst.insert(2, 'z');
  lst.insert(3, 'b');

  LinkedList<char> sorted = sort(lst);

  REQUIRE(sorted.getEntry(0) == 'a');
  REQUIRE(sorted.getEntry(1) == 'b');
  REQUIRE(sorted.getEntry(2) == 'c');
  REQUIRE(sorted.getEntry(3) == 'z');

}