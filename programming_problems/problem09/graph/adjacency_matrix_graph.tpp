#include "adjacency_matrix_graph.hpp"

template <typename LabelType>
AdjacencyMatrixGraph<LabelType>::AdjacencyMatrixGraph()
{
    int initial = 4;
    for (int i = 0; i < initial; i++)
    {
        std::vector<bool> new_row(initial, 0);
        edges.push_back(new_row);
    }
    num_edges = 0;
    num_vertices = 0;
}

template <typename LabelType>
int AdjacencyMatrixGraph<LabelType>::getNumVertices() const
{
    return vertex_set.size();
}

template <typename LabelType>
int AdjacencyMatrixGraph<LabelType>::getNumEdges() const
{
    return num_edges;
}

template <typename LabelType>
bool AdjacencyMatrixGraph<LabelType>::add(LabelType start, LabelType end)
{

    if (vertex_set.size() > 0)
    {
        if (!(vertex_set.count(start) > 0 || vertex_set.count(end) > 0))
        {
            return false;
        }
    }

    if (!vertex_set.count(start))
    {
        vertex_set.insert(start);
        vertex_indices[start] = num_vertices++;
    }

    if (!vertex_set.count(end))
    {
        vertex_set.insert(end);
        vertex_indices[end] = num_vertices++;
    }

    if (num_vertices > edges.size())
    {
        std::vector<std::vector<bool>> new_edges;
        for (int i = 0; i < edges.size() * 2; i++)
        {
            if (i < edges.size())
            {
                std::vector<bool> new_row(edges[i]);
                new_row.resize(edges.size() * 2);
                new_edges.push_back(new_row);
            }
            else
            {
                std::vector<bool> new_row(edges.size() * 2, 0);
                new_edges.push_back(new_row);
            }
        }

        edges = new_edges;
    }

    auto start_index = vertex_indices[start]; // auto is magical
    auto end_index = vertex_indices[end];

    // check if edges in array
    if (!edges[start_index][end_index])
    {
        edges[start_index][end_index] = true;
        edges[end_index][start_index] = true;
        num_edges++;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename LabelType>
bool AdjacencyMatrixGraph<LabelType>::remove(LabelType start, LabelType end)
{
    // make sure valid index
    if (!vertex_set.count(start))
    {
        return false;
    }

    if (!vertex_set.count(end))
    {
        return false;
    }

    auto start_index = vertex_indices[start];
    auto end_index = vertex_indices[end];

    if (edges[start_index][end_index])
    {
        edges[start_index][end_index] = false;
        edges[end_index][start_index] = false;
        num_edges--;

        // all false
        if (std::find(edges[start_index].begin(), edges[start_index].end(), true) == edges[start_index].end())
        {
            vertex_set.erase(start);
            num_vertices--;
        }

        if (std::find(edges[end_index].begin(), edges[end_index].end(), true) == edges[end_index].end())
        {
            vertex_set.erase(end);
            num_vertices--;
        }

        return true;
    }
    else
    {
        // edge don't exsist
        return false;
    }
}

template <typename LabelType>
void AdjacencyMatrixGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType &)) {}

template <typename LabelType>
void AdjacencyMatrixGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType &)) {}