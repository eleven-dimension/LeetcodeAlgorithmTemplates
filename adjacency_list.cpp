#include <bits/stdc++.h>

struct Edge {
    size_t to;
    size_t weight;

    Edge(size_t to, size_t weight) : to(to), weight(weight) {}
};

class Graph {
public:
    Graph(size_t number_of_vertices) : number_of_vertices_(number_of_vertices) {
        adjacency_list_.resize(number_of_vertices);
    }

    void addEdge(size_t u, size_t v, size_t weight) {
        adjacency_list_[u].emplace_back(v, weight);
        adjacency_list_[v].emplace_back(u, weight);
    }

    std::vector<Edge> getOutgoingEdges(size_t u) {
        return adjacency_list_.at(u);
    }

private:
    std::vector<std::vector<Edge>> adjacency_list_;
    size_t number_of_vertices_;
};