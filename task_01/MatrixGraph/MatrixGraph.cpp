#include <iostream>

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verticesCount) {
    verticesCount = verticesCount;
    matrix = new bool*[verticesCount];
    for (int i = 0; i < verticesCount; i++)
        matrix[i] = new bool[verticesCount];
    for (int i = 0; i < verticesCount; i++)
        for (int j = 0; j < verticesCount; j++)
            matrix[i][j] = false;
}

MatrixGraph::MatrixGraph(const IGraph& graph) {
    verticesCount = graph.VerticesCount();
    matrix = new bool*[verticesCount];
    for (int i = 0; i < verticesCount; i++)
        matrix[i] = new bool[verticesCount];
    for (int i = 0; i < verticesCount; i++)
        for (int j = 0; j < verticesCount; j++)
            matrix[i][j] = false;
    for (int i = 0; i < verticesCount; i++)
    {
        std::vector<int> next = graph.GetNextVertices(i);
        for (size_t j = 0; j < next.size(); j++)
            matrix[i][next[j]] = true;
    }
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < verticesCount; ++i)
        delete [] matrix[i];
    delete [] matrix;
    std::cout << "~MatrixGraph" << std::endl;
}
    
// Добавление ребра от from к to.
void MatrixGraph::AddEdge(int from, int to) {
    matrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {

    std::vector<int> result;
    for (int next = 0; next < verticesCount; next++)
    {
        if (matrix[vertex][next])
        {
            result.push_back(next);
        }
    }
    return result;
}
std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int from = 0; from < verticesCount; from++)
    {
        if (matrix[from][vertex])
        {
            result.push_back(from);
        }
    }
    return result;
}