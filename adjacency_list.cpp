#include <bits/stdc++.h>

struct Edge {
    int to;
    int weight;

    Edge(int to, int weight) : to(to), weight(weight) {}
};

class Graph {
public:
    Graph(int number_of_vertices) : number_of_vertices_(number_of_vertices) {
        adjacency_list_.resize(number_of_vertices);
    }

    void addEdge(int u, int v, int weight) {
        adjacency_list_[u].emplace_back(v, weight);
        adjacency_list_[v].emplace_back(u, weight);
    }

    std::vector<Edge> getOutgoingEdges(int u) {
        return adjacency_list_.at(u);
    }

private:
    std::vector<std::vector<Edge>> adjacency_list_;
    size_t number_of_vertices_;
};