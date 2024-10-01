#include <bits/stdc++.h>

struct Edge {
  size_t to;
  size_t weight;

  Edge(size_t to, size_t weight) : to(to), weight(weight) {}
};

class Graph {
 public:
  enum class EdgeType { DIRECTED, UNDIRECTED };

  Graph(size_t number_of_vertices, EdgeType type = EdgeType::UNDIRECTED)
      : adjacency_list_(number_of_vertices), edge_type_(type) {}

  void addEdge(size_t u, size_t v, size_t weight) {
    adjacency_list_[u].emplace_back(v, weight);
    if (edge_type_ == EdgeType::UNDIRECTED) {
      adjacency_list_[v].emplace_back(u, weight);
    }
  }

  const std::vector<Edge>& getOutgoingEdges(size_t u) const {
    return adjacency_list_[u];
  }

  size_t number_of_vertices() const { return adjacency_list_.size(); }

 private:
  EdgeType edge_type_;
  std::vector<std::vector<Edge>> adjacency_list_;
};

int main() {
  {
    Graph graph(3, Graph::EdgeType::DIRECTED);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);

    std::cout << "Nodes adjacent to the 1-st node: ";
    for (auto& edge : graph.getOutgoingEdges(1)) {
      std::cout << edge.to << " ";
    }
    std::cout << std::endl;
  }

  {
    Graph graph(3);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);

    std::cout << "Nodes adjacent to the 1-st node: ";
    for (auto& edge : graph.getOutgoingEdges(1)) {
      std::cout << edge.to << " ";
    }
    std::cout << std::endl;
  }
}