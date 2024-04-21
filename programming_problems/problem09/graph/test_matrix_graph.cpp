#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "adjacency_list_graph.hpp"
#include "adjacency_matrix_graph.hpp"

typedef AdjacencyMatrixGraph<int> GraphType;
// typedef AdjacencyListGraph<int> GraphType;


TEST_CASE("Test Construction", "[construction]") {
  GraphType  matrixGraph;
  REQUIRE(matrixGraph.getNumVertices() == 0);
}

TEST_CASE("Test add", "[add]") {
    GraphType matrixGraph;

    REQUIRE(matrixGraph.add(0, 1));
    REQUIRE(matrixGraph.getNumVertices() == 2);
    REQUIRE(matrixGraph.getNumEdges() == 1);

    REQUIRE(matrixGraph.add(1, 2));
    REQUIRE(matrixGraph.getNumVertices() == 3);
    REQUIRE(matrixGraph.getNumEdges() == 2);

    REQUIRE(matrixGraph.add(2, 0));
    REQUIRE(matrixGraph.getNumVertices() == 3);
    REQUIRE(matrixGraph.getNumEdges() == 3);

    REQUIRE_FALSE(matrixGraph.add(2, 0)); 
    REQUIRE(matrixGraph.getNumEdges() == 3); 
}


TEST_CASE("Test remove", "[remove]") {
    GraphType matrixGraph;

    REQUIRE(matrixGraph.add(0, 1));
    REQUIRE(matrixGraph.add(1, 8));
    REQUIRE(matrixGraph.add(1, 2));
    REQUIRE(matrixGraph.add(3, 2));
    REQUIRE(matrixGraph.add(1, 3));
    REQUIRE(matrixGraph.add(2, 55));

    REQUIRE(matrixGraph.getNumEdges() == 6);
    REQUIRE_FALSE(matrixGraph.remove(0, 20));

    REQUIRE(matrixGraph.remove(8, 1));
    REQUIRE(matrixGraph.getNumVertices() == 5);
    REQUIRE(matrixGraph.getNumEdges() == 5);

    REQUIRE(matrixGraph.remove(0, 1));
    REQUIRE(matrixGraph.getNumVertices() == 4);
    REQUIRE(matrixGraph.getNumEdges() == 4);

    REQUIRE(matrixGraph.remove(1, 2));
    REQUIRE(matrixGraph.remove(3, 1));
    REQUIRE(matrixGraph.getNumVertices() == 3);
    REQUIRE(matrixGraph.getNumEdges() == 2);
}


TEST_CASE("Test getNumEdges", "[getNumEdges]") 
{
  GraphType matrixGraph;

  REQUIRE(matrixGraph.add(0, 1));
  REQUIRE(matrixGraph.add(1, 8));
  REQUIRE(matrixGraph.add(1, 2));
  REQUIRE(matrixGraph.add(3, 2));
  REQUIRE(matrixGraph.add(1, 3));
  REQUIRE(matrixGraph.add(2, 55));

  REQUIRE(matrixGraph.getNumEdges() == 6);
}

TEST_CASE("Test getNumVertices", "[getNumVertices]") {
  GraphType matrixGraph;

  REQUIRE(matrixGraph.add(0, 1));
  REQUIRE(matrixGraph.add(1, 2));
  REQUIRE(matrixGraph.add(2, 0));
  REQUIRE(matrixGraph.add(2, 3));
  REQUIRE(matrixGraph.add(3, 4));

  REQUIRE(matrixGraph.getNumVertices() == 5);

  matrixGraph.add(4, 5);
  REQUIRE(matrixGraph.getNumVertices() == 6);
}
