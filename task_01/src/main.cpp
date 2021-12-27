/*
Дан базовый интерфейс для представления ориентированного графа.
Необходимо написать несколько реализаций интерфейса:
ListGraph, хранящий граф в виде массива списков смежности,
MatrixGraph, хранящий граф в виде матрицы смежности,
SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
ArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.
*/

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "ArcGraph.h"
#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"

void dfs(const IGraph& graph, void (*callback)(int v))
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::stack<int> stack;
    stack.push(0);
    for (int i = 0; i < graph.VerticesCount(); i++) {
        stack.push(i);
        while (!stack.empty()) {
            int curVex = stack.top();
            stack.pop();
            if (!visited[curVex]) {
                callback(curVex);
                visited[curVex] = true;
            }
            std::vector<int> children = graph.GetNextVertices(curVex);
            for (int i = children.size() - 1; i >= 0; i--) {
                int child = children[i];
                if (!visited[child]) {
                    stack.push(child);
                }
            }
        }
    }
}

void bfs(const IGraph& graph, void (*callback)(int v))
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> q;
    for (int vertex = 0; vertex < graph.VerticesCount(); vertex++) {
        if (!visited[vertex]) {
            visited[vertex] = true;
            q.push(vertex);
            while (!q.empty()) {
                int curVex = q.front();
                q.pop();
                callback(curVex);
                std::vector<int> children = graph.GetNextVertices(curVex);
                for (auto& child : children) {
                    if (!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
        }
    }
}

int main()
{
    IGraph* listGraph = new ListGraph(9);
    listGraph->AddEdge(0, 1);
    listGraph->AddEdge(0, 7);
    listGraph->AddEdge(0, 8);
    listGraph->AddEdge(1, 2);
    listGraph->AddEdge(1, 5);
    listGraph->AddEdge(2, 3);
    listGraph->AddEdge(3, 4);
    listGraph->AddEdge(4, 2);
    listGraph->AddEdge(6, 0);

    std::cout << "This is ListGraph" << std::endl;
    std::cout << "----------DFS---------" << std::endl;
    dfs(*listGraph, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "----------BFS---------" << std::endl;
    bfs(*listGraph, [](int v) {
        std::cout << v << std::endl;
    });

    IGraph* matrixGraph = new MatrixGraph(*listGraph);
    std::cout << "This is MatrixGraph" << std::endl;
    std::cout << "----------DFS---------" << std::endl;
    dfs(*matrixGraph, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "----------BFS---------" << std::endl;
    bfs(*matrixGraph, [](int v) {
        std::cout << v << std::endl;
    });

    IGraph* setGraph = new SetGraph(*matrixGraph);
    std::cout << "This is SetGraph" << std::endl;
    std::cout << "----------DFS---------" << std::endl;
    dfs(*setGraph, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "----------BFS---------" << std::endl;
    bfs(*setGraph, [](int v) {
        std::cout << v << std::endl;
    });

    IGraph* arcGraph = new ArcGraph(*setGraph);
    std::cout << "This is ArcGraph" << std::endl;
    std::cout << "----------DFS---------" << std::endl;
    dfs(*arcGraph, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "----------BFS---------" << std::endl;
    bfs(*arcGraph, [](int v) {
        std::cout << v << std::endl;
    });

    IGraph* secondListGraph = new ListGraph(*arcGraph);
    std::cout << "This is second ListGraph" << std::endl;
    std::cout << "----------DFS---------" << std::endl;
    dfs(*secondListGraph, [](int v) {
        std::cout << v << std::endl;
    });
    std::cout << "----------BFS---------" << std::endl;
    bfs(*secondListGraph, [](int v) {
        std::cout << v << std::endl;
    });

    delete listGraph;
    delete matrixGraph;
    delete setGraph;
    delete arcGraph;
    delete secondListGraph;

    return 0;
}