#include "adjacency_list_graph.hpp"

template <typename LabelType>
AdjacencyListGraph<LabelType>::AdjacencyListGraph()
{
    num_edges = 0;
    num_vertices = 0;
}

template <typename LabelType>
int AdjacencyListGraph<LabelType>::getNumVertices() const
{
    return vertex_set.size();
}

template <typename LabelType>
int AdjacencyListGraph<LabelType>::getNumEdges() const
{
    return num_edges;
}

template <typename LabelType>
bool AdjacencyListGraph<LabelType>::add(LabelType start, LabelType end)
{
    //check if empty
    if (vertex_set.size() > 0)
    {
        if (!(vertex_set.count(start) > 0 || vertex_set.count(end) > 0))
        {
            return false;
        }
    }

    //create list if not exist
    if (!vertex_set.count(start))
    {
        vertex_set.insert(start);
        std::vector<LabelType> new_vec;
        adj_list[start] = new_vec;
    }

    //create list if not exist
    if (!vertex_set.count(end))
    {
        vertex_set.insert(end);
        std::vector<LabelType> new_vec;
        adj_list[end] = new_vec;
    }

    //if edge doesn't exist, add
    if (std::find(adj_list[start].begin(), adj_list[start].end(), end) == adj_list[start].end())
    {
        adj_list[start].push_back(end);
        adj_list[end].push_back(start);
        num_edges++;
        return true;
    }

    return false;
}

template <typename LabelType>
bool AdjacencyListGraph<LabelType>::remove(LabelType start, LabelType end)
{
    //if start and end don't exist
    if (!vertex_set.count(start) || !vertex_set.count(end))
    {
        return false;
    }

    if (std::find(adj_list[start].begin(), adj_list[start].end(), end) == adj_list[start].end())
    {
        return false;
    }

    //remove from list
    adj_list[start].erase(std::remove(adj_list[start].begin(), adj_list[start].end(), end), adj_list[start].end());
    adj_list[end].erase(std::remove(adj_list[end].begin(), adj_list[end].end(), start), adj_list[end].end());
    num_edges--;

    //remove from vertex
    if (adj_list[start].size() == 0)
    {
        vertex_set.erase(start);
    }
    if (adj_list[end].size() == 0)
    {
        vertex_set.erase(end);
    }

    return true;
}

template <typename LabelType>
void AdjacencyListGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType &)) {}

template <typename LabelType>
void AdjacencyListGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType &)) {}