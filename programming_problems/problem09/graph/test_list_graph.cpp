#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "adjacency_list_graph.hpp"
#include "adjacency_matrix_graph.hpp"

// typedef AdjacencyMatrixGraph<int> GraphType;
typedef AdjacencyListGraph<int> GraphType;


TEST_CASE("Test Construction", "[construction]") {
  GraphType  listGraph;
  REQUIRE(listGraph.getNumVertices() == 0);
}

TEST_CASE("Test add", "[add]") {
    GraphType listGraph;

    REQUIRE(listGraph.add(0, 1));
    REQUIRE(listGraph.getNumVertices() == 2);
    REQUIRE(listGraph.getNumEdges() == 1);

    REQUIRE(listGraph.add(1, 2));
    REQUIRE(listGraph.getNumVertices() == 3);
    REQUIRE(listGraph.getNumEdges() == 2);

    REQUIRE(listGraph.add(2, 0));
    REQUIRE(listGraph.getNumVertices() == 3);
    REQUIRE(listGraph.getNumEdges() == 3);

    REQUIRE_FALSE(listGraph.add(2, 0)); 
    REQUIRE(listGraph.getNumEdges() == 3); 
}


TEST_CASE("Test remove", "[remove]") {
    GraphType listGraph;

    REQUIRE(listGraph.add(0, 1));
    REQUIRE(listGraph.add(1, 8));
    REQUIRE(listGraph.add(1, 2));
    REQUIRE(listGraph.add(3, 2));
    REQUIRE(listGraph.add(1, 3));
    REQUIRE(listGraph.add(2, 55));

    REQUIRE(listGraph.getNumEdges() == 6);
    REQUIRE_FALSE(listGraph.remove(0, 20));

    REQUIRE(listGraph.remove(8, 1));
    REQUIRE(listGraph.getNumVertices() == 5);
    REQUIRE(listGraph.getNumEdges() == 5);

    REQUIRE(listGraph.remove(0, 1));
    REQUIRE(listGraph.getNumVertices() == 4);
    REQUIRE(listGraph.getNumEdges() == 4);

    REQUIRE(listGraph.remove(1, 2));
    REQUIRE(listGraph.remove(3, 1));
    REQUIRE(listGraph.getNumVertices() == 3);
    REQUIRE(listGraph.getNumEdges() == 2);
}


TEST_CASE("Test getNumEdges", "[getNumEdges]") 
{
  GraphType listGraph;

  REQUIRE(listGraph.add(0, 1));
  REQUIRE(listGraph.add(1, 8));
  REQUIRE(listGraph.add(1, 2));
  REQUIRE(listGraph.add(3, 2));
  REQUIRE(listGraph.add(1, 3));
  REQUIRE(listGraph.add(2, 55));

  REQUIRE(listGraph.getNumEdges() == 6);
}

TEST_CASE("Test getNumVertices", "[getNumVertices]") {
  GraphType listGraph;

  REQUIRE(listGraph.add(0, 1));
  REQUIRE(listGraph.add(1, 2));
  REQUIRE(listGraph.add(2, 0));
  REQUIRE(listGraph.add(2, 3));
  REQUIRE(listGraph.add(3, 4));

  REQUIRE(listGraph.getNumVertices() == 5);

  listGraph.add(4, 5);
  REQUIRE(listGraph.getNumVertices() == 6);
}
