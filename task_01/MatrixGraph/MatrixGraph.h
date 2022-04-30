#ifndef MATRIX_GRAPH_H_

#define MATRIX_GRAPH_H_

#include <iostream>
#include <vector>

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(int verticesCount);

    MatrixGraph(const IGraph& graph);

    ~MatrixGraph();

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int verticesCount;
    bool** matrix;
};

#endif