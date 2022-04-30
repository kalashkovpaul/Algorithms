/*
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей 
между какими-то вершинами. Найдите количество различных кратчайших путей между заданными 
вершинами.
*/
#include <iostream>
#include <queue>
#include <vector>

struct IGraph {
    virtual ~IGraph()
    {
    }

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

int bfs(const IGraph& graph, int from, int to)
{
    std::queue<int> q;
    std::vector<int> pathCount(graph.VerticesCount(), 1);
    std::vector<int> dist(graph.VerticesCount(), graph.VerticesCount());
    q.push(from);
    dist[from] = 0;
    while (!q.empty()) {
        int curVex = q.front();
        q.pop();

        std::vector<int> children = graph.GetNextVertices(curVex);
        for (auto& child : children) {
            if (dist[child] == graph.VerticesCount() || dist[child] > dist[curVex] + 1) {
                dist[child] = dist[curVex] + 1;
                pathCount[child] = pathCount[curVex];
                q.push(child);
            } else if (dist[child] == dist[curVex] + 1) {
                pathCount[child] += pathCount[curVex];
            }
        }
    }
    if (dist[to] == graph.VerticesCount())
        pathCount[to] = 0;
    return pathCount[to];
}

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

ListGraph::ListGraph(int verticesCount)
{
    vertices.resize(verticesCount);
}

ListGraph::ListGraph(const IGraph& graph)
{
    vertices.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); i++) {
        vertices[i] = graph.GetNextVertices(i);
    }
}

ListGraph::~ListGraph()
{
}

// Добавление ребра от from к to.
void ListGraph::AddEdge(int from, int to)
{
    vertices[from].push_back(to);
    vertices[to].push_back(from);
}

int ListGraph::VerticesCount() const
{
    return vertices.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
    std::vector<int> result(vertices[vertex].begin(), vertices[vertex].end());
    return result;
}
std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;
    for (size_t parent = 0; parent < vertices.size(); parent++) {
        for (auto& child : vertices[parent]) {
            if (child == vertex) {
                result.push_back(parent);
                break;
            }
        }
    }
    return result;
}

int main()
{
    int verticesAmount = 0;
    int edgesAmount = 0;
    int from = 0, to = 0;
    std::cin >> verticesAmount >> edgesAmount;
    IGraph* listGraph = new ListGraph(verticesAmount);
    for (int i = 0; i < edgesAmount; i++) {
        std::cin >> from >> to;
        listGraph->AddEdge(from, to);
    }
    std::cin >> from >> to;
    std::cout << bfs(*listGraph, from, to) << std::endl;

    delete listGraph;
    return 0;
}