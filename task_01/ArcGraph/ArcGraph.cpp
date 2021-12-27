#include <iostream>
#include <unordered_set>

#include "ArcGraph.h"

ArcGraph::ArcGraph(int vCount)
{
    verticesCount = vCount;
}

ArcGraph::ArcGraph(const IGraph& graph)
{
    verticesCount = graph.VerticesCount();
    for (int i = 0; i < graph.VerticesCount(); i++) {
        std::vector<int> next = graph.GetNextVertices(i);
        for (size_t j = 0; j < next.size(); j++) {
            arcs.push_back(std::make_pair(i, next[j]));
        }
    }
}

ArcGraph::~ArcGraph()
{
    std::cout << "~ArcGraph" << std::endl;
}

// Добавление ребра от from к to.
void ArcGraph::AddEdge(int from, int to)
{
    arcs.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const
{
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
    std::vector<int> result;
    for (auto& itr : arcs) {
        if (itr.first == vertex)
            result.push_back(itr.second);
    }
    return result;
}
std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;
    for (auto& itr : arcs) {
        if (itr.second == vertex)
            result.push_back(itr.first);
    }
    return result;
}