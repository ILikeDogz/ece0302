#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

TEST_CASE("Testing Priority Queue", "[priority queue]") {
  typedef SortedList<int, List<int>> SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;

  REQUIRE(pq.isEmpty());
  pq.add(7);
  REQUIRE_FALSE(pq.isEmpty());
  REQUIRE(pq.peek() == 7);

  pq.add(-7);
  REQUIRE_FALSE(pq.isEmpty());
  REQUIRE(pq.peek() == 7);

  pq.remove();
  REQUIRE_FALSE(pq.isEmpty());
  REQUIRE(pq.peek() == -7);

  pq.remove();
  REQUIRE(pq.isEmpty());

  pq.add(21);
  pq.add(14);
  pq.add(7);
  REQUIRE_FALSE(pq.isEmpty());
  REQUIRE(pq.peek() == 21);
  pq.add(0);
  REQUIRE(pq.peek() == 21);
  pq.add(28);
  REQUIRE(pq.peek() == 28);
  pq.remove();
  REQUIRE(pq.peek() == 21);
  pq.add(42);
  pq.add(35);
  pq.add(-7);
  REQUIRE(pq.peek() == 42);
  pq.remove();
  REQUIRE(pq.peek() == 35);

  // TODO

}


