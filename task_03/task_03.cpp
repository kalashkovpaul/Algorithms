/*
Требуется отыскать самый выгодный маршрут между городами. 
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между 
ними.
*/

#include <bits/stdc++.h>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

typedef std::pair<int, int> intPair;

class Graph {
public:
    Graph(int verticesCount);

    ~Graph();

    void AddEdge(int from, int to, int weight);

    int VerticesCount() const;

    int findWay(int from, int to);

private:
    int verticesCount;
    std::list<intPair>* edges;
    std::vector<int> distances;
};

Graph::Graph(int vCount)
{
    verticesCount = vCount;
    distances.resize(vCount);
    edges = new std::list<intPair>[verticesCount];
}

Graph::~Graph()
{
    delete[] edges;
}

void Graph::AddEdge(int from, int to, int weight)
{
    edges[from].push_back(std::make_pair(to, weight));
    edges[to].push_back(std::make_pair(from, weight));
}

int Graph::VerticesCount() const
{
    return verticesCount;
}

int Graph::findWay(int from, int to)
{
    std::fill(distances.begin(), distances.end(), INT_MAX);
    distances[from] = 0;
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> q;
    q.push(std::make_pair(0, from));
    int parent = 0;
    while (!q.empty()) {
        parent = q.top().second;
        q.pop();

        std::list<intPair>::iterator i;
        for (i = edges[parent].begin(); i != edges[parent].end(); i++) {
            int child = i->first;
            int weight = i->second;
            if (distances[child] > distances[parent] + weight) {
                distances[child] = distances[parent] + weight;
                q.push(std::make_pair(distances[child], child));
            }
        }
    }
    return distances[to];
}

int main()
{
    int verticesAmount = 0;
    int edgesAmount = 0;
    int from = 0, to = 0, weight;
    std::cin >> verticesAmount >> edgesAmount;
    Graph* graph = new Graph(verticesAmount);
    for (int i = 0; i < edgesAmount; i++) {
        std::cin >> from >> to >> weight;
        graph->AddEdge(from, to, weight);
    }
    std::cin >> from >> to;
    std::cout << graph->findWay(from, to) << std::endl;

    delete graph;
    return 0;
}