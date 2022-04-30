#ifndef ARC_GRAPH_H_

#define ARC_GRAPH_H_

#include <iostream>
#include <utility>
#include <vector>

#include "IGraph.h"

class ArcGraph : public IGraph {
public:
    ArcGraph(int verticesCount);

    ArcGraph(const IGraph& graph);

    ~ArcGraph();

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int verticesCount;
    std::vector<std::pair<int, int>> arcs;
};

#endif