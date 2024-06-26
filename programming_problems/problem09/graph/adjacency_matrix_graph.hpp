#ifndef _ADJACENCY_MATRIX_GRAPH_H_
#define _ADJACENCY_MATRIX_GRAPH_H_

#include "abstract_graph.hpp"
#include <map>
#include <algorithm>
#include <set>

template <typename LabelType>
class AdjacencyMatrixGraph: public AbstractGraph<LabelType>
{
    public:

        AdjacencyMatrixGraph();

        int getNumVertices() const;
        
        int getNumEdges() const;

        bool add(LabelType start, LabelType end);

        bool remove(LabelType start, LabelType end);

        void depthFirstTraversal(LabelType start, void visit(LabelType&));

        void breadthFirstTraversal(LabelType start, void visit(LabelType&));

    private: 
        std::map<LabelType, int> vertex_indices;
        std::set<LabelType> vertex_set;
        std::vector<std::vector<bool>> edges;
        int num_edges;
        int num_vertices;

  
};

#include "adjacency_matrix_graph.tpp"

#endif 
