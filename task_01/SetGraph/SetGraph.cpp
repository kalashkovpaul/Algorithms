#include <algorithm>
#include <iostream>

#include "SetGraph.h"

SetGraph::SetGraph(int verticesCount)
{
    vertices.resize(verticesCount);
}

SetGraph::SetGraph(const IGraph& graph)
{
    vertices.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); i++) {
        std::vector<int> next = graph.GetNextVertices(i);
        for (size_t j = 0; j < next.size(); j++) {
            vertices[i].insert(next[j]);
        }
    }
}

SetGraph::~SetGraph()
{
    std::cout << "~SetGraph" << std::endl;
}

// Добавление ребра от from к to.
void SetGraph::AddEdge(int from, int to)
{
    vertices[from].insert(to);
}

int SetGraph::VerticesCount() const
{
    return vertices.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    std::unordered_set<int>::iterator itr;
    std::vector<int> result;
    for (auto& itr : vertices[vertex]) {
        result.push_back(itr);
    }
    std::sort(result.begin(), result.end());
    return result;
}
std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;
    for (size_t from = 0; from < vertices.size(); from++) {
        if (vertices[from].find(vertex) != vertices[from].end()) {
            result.push_back(from);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}