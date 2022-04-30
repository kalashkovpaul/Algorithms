#ifndef LIST_GRAPH_H_

#define LIST_GRAPH_H_

#include <iostream>
#include <vector>

#include "IGraph.h"

class ListGraph : public IGraph {
public:
    ListGraph(int verticesCount);

    ListGraph(const IGraph& graph);

    ~ListGraph();

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> vertices;
};

#endif