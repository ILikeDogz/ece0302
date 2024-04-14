#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "queue.hpp"

TEST_CASE("Testing all", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(12);
  REQUIRE(!queue.isEmpty());
  REQUIRE(queue.peekFront() == 12);

  queue.enqueue(-4);
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 12);

  queue.dequeue();
  queue.dequeue();
  REQUIRE(queue.isEmpty());

  queue.enqueue(241);
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 241);

  queue.enqueue(45);
  REQUIRE(!queue.isEmpty());
  REQUIRE(queue.peekFront() == 241);

  queue.enqueue(62);
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 241);

  Queue<int, List<int>> another_queue;
  another_queue = queue;

  REQUIRE_FALSE(another_queue.isEmpty());
  REQUIRE(another_queue.peekFront() == 241);
  another_queue.dequeue();
  REQUIRE(another_queue.peekFront() == 45);
  another_queue.dequeue();
  REQUIRE(another_queue.peekFront() == 62);
}

TEST_CASE("Testing all 2", "[queue]") {
  Queue<int, List<int>> queue;

  REQUIRE(queue.isEmpty());
  for(int i = 0; i < 10; i++){
    queue.enqueue(i);
  }

  REQUIRE(!queue.isEmpty());
  REQUIRE(queue.peekFront() == 0);
  Queue<int, List<int>> another_queue;
  another_queue = queue;

  REQUIRE(queue.peekFront() == another_queue.peekFront());
  for(int i = 0; i < 10; i++){
    REQUIRE(queue.peekFront() == i);
    queue.dequeue();
  }
  REQUIRE(queue.isEmpty());
  REQUIRE_THROWS(queue.dequeue());

}