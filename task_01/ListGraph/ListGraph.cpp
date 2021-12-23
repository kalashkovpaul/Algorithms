#include <iostream>

#include "ListGraph.h"

ListGraph::ListGraph(int verticesCount) {
    vertices.resize(verticesCount);
}

ListGraph::ListGraph(const IGraph& graph) {
    vertices.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        vertices[i] = graph.GetNextVertices(i);
    }
}

ListGraph::~ListGraph() {
    std::cout << "~ListGraph" << std::endl;
}
    
// Добавление ребра от from к to.
void ListGraph::AddEdge(int from, int to) {
    vertices[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return vertices.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result(vertices[vertex].begin(), vertices[vertex].end());
    return result;
}
std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (size_t parent = 0; parent < vertices.size(); parent++)
    {
        for (auto& child : vertices[parent])
        {
            if (child == vertex)
            {
                result.push_back(parent);
                break;
            }
        }
    }
    return result;
}