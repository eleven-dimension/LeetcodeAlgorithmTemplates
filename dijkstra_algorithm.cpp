#include <bits/stdc++.h>

struct Edge {
    size_t to;
    size_t weight;

    Edge(size_t to, size_t weight) : to(to), weight(weight) {}

    bool operator==(const Edge& other) const {
        return to == other.to && weight == other.weight;
    }
};

enum class EdgeType { DIRECTED, UNDIRECTED };

class Graph {
public:
    Graph(size_t number_of_vertices, EdgeType type = EdgeType::UNDIRECTED) : adjacency_list_(number_of_vertices), edge_type_(type) {}

    void addEdge(size_t u, size_t v, size_t weight) {
        adjacency_list_[u].emplace_back(v, weight);
        if (edge_type_ == EdgeType::UNDIRECTED) {
            adjacency_list_[v].emplace_back(u, weight);
        }
    }

    const std::vector<Edge>& getOutgoingEdges(size_t u) const {
        return adjacency_list_[u];
    }

    size_t number_of_vertices() const {
        return adjacency_list_.size();
    }

private:
    EdgeType edge_type_;
    std::vector<std::vector<Edge>> adjacency_list_;
};


class Dijkstra {
public:
    Dijkstra(size_t number_of_vertices, EdgeType type = EdgeType::UNDIRECTED) 
        : graph_(number_of_vertices, type), 
          edge_type_(type), 
          first_edge_added_(false),
          has_same_weights_(true) {}

    void AddEdge(size_t u, size_t v, size_t weight) {
        if (!first_edge_added_) {
            initial_weight_ = weight;
            first_edge_added_ = true;
        } else if (has_same_weights_ && weight != initial_weight_) {
            has_same_weights_ = false;
        }
        graph_.addEdge(u, v, weight);
    }

    std::vector<size_t> CalcShortestPath(size_t start) { 
        if (has_same_weights_) {
            return DoDijkstra<std::queue<std::pair<size_t, size_t>>>(start, std::nullopt, std::nullopt);
        } else {
            return DoDijkstra<std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<>>>(start, std::nullopt, std::nullopt);
        }
    }

    size_t CalcShortestPath(size_t start, size_t target, std::optional<std::pair<size_t, size_t>> edge_deleted) { 
        if (has_same_weights_) {
            return DoDijkstra<std::queue<std::pair<size_t, size_t>>>(start, target, edge_deleted)[target];
        } else {
            return DoDijkstra<std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<>>>(start, target, edge_deleted)[target];
        }
    }

private:
    Graph graph_;
    EdgeType edge_type_;

    bool has_same_weights_;
    size_t initial_weight_;
    bool first_edge_added_;

    template <typename Container>
    std::vector<size_t> DoDijkstra(size_t start, std::optional<size_t> target, std::optional<std::pair<size_t, size_t>> edge_deleted) {
        int n = graph_.number_of_vertices();
        std::vector<size_t> distance(n, std::numeric_limits<size_t>::max());

        Container q;
        q.emplace(0, start);
        distance[start] = 0;

        while (q.size()) {
            size_t cur_dis, cur_node;
            if constexpr (std::is_same_v<Container, std::queue<std::pair<size_t, size_t>>>) {
                std::tie(cur_dis, cur_node) = q.front();
            } else if constexpr (std::is_same_v<Container, std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<>>>) {
                std::tie(cur_dis, cur_node) = q.top();
            } else {
                throw std::invalid_argument("Template parameter not supported");
            }

            q.pop();
            if (cur_dis > distance[cur_node]) {
                continue;
            }

            for (const auto& edge : graph_.getOutgoingEdges(cur_node)) {
                if (edge_deleted == std::make_pair(cur_node, edge.to) || edge_deleted == std::make_pair(edge.to, cur_node)) {
                    continue;
                }

                size_t new_dis = cur_dis + edge.weight;
                if (new_dis < distance[edge.to]) {
                    distance[edge.to] = new_dis;
                    q.emplace(new_dis, edge.to);
                    if (edge.to == target) {
                        return distance;
                    }
                }
            }
        }
        return distance;
    }
};

using namespace std;

class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        Dijkstra dijkstra(n);
        for (auto& edge : edges) {
            dijkstra.AddEdge(edge[0], edge[1], 1);
        }
        size_t ans = std::numeric_limits<size_t>::max();
        for (auto& edge : edges) {
            auto min_dis = dijkstra.CalcShortestPath(edge[0], edge[1], make_pair(edge[0], edge[1]));
            if (min_dis != numeric_limits<size_t>::max()) {
                ans = min(ans, min_dis + 1);
            }
        }
        return ans == std::numeric_limits<size_t>::max() ? -1 : ans;
    }
};

int main() {
    {
        int n = 7;
        vector<vector<int>> edges = {{0,1},{1,2},{2,0},{3,4},{4,5},{5,6},{6,3}};
        Solution sol;
        cout << sol.findShortestCycle(n, edges) << endl;
    }
    {
        int n = 4;
        vector<vector<int>> edges = {{0,1},{0,2}};
        Solution sol;
        cout << sol.findShortestCycle(n, edges) << endl;
    }
}