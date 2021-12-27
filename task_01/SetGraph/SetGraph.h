#ifndef SET_GRAPH_H_

#define SET_GRAPH_H_

#include <iostream>
#include <unordered_set>
#include <vector>

#include "IGraph.h"

class SetGraph : public IGraph {
public:
    SetGraph(int verticesCount);

    SetGraph(const IGraph& graph);

    ~SetGraph();

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> vertices;
};

#endif