#include <bits/stdc++.h>

struct Edge {
    size_t to;
    size_t weight;

    Edge(size_t to, size_t weight) : to(to), weight(weight) {}
};

class Graph {
public:
    Graph(size_t number_of_vertices) : adjacency_list_(number_of_vertices) {}

    void addEdge(size_t u, size_t v, size_t weight) {
        adjacency_list_[u].emplace_back(v, weight);
        adjacency_list_[v].emplace_back(u, weight);
    }

    const std::vector<Edge>& getOutgoingEdges(size_t u) const {
        return adjacency_list_[u];
    }

    size_t number_of_vertices() const {
        return adjacency_list_.size();
    }

private:
    std::vector<std::vector<Edge>> adjacency_list_;
};
