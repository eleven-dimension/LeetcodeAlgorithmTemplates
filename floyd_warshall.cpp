#include <bits/stdc++.h>

class FloydWarshall {
public:
    FloydWarshall(size_t number_of_vertices) 
        : number_of_vertices_(number_of_vertices), 
          distance_(number_of_vertices, std::vector<size_t>(number_of_vertices, INF)) {
        for (size_t i = 0; i < number_of_vertices; ++i) {
            distance_[i][i] = 0;
        }
    }

    void addEdge(size_t from, size_t to, size_t weight) {
        distance_[from][to] = std::min(distance_[from][to], weight);
        distance_[to][from] = std::min(distance_[to][from], weight);
    }

    void computeShortestPaths() {
        for (size_t k = 0; k < number_of_vertices_; ++k) {
            for (size_t i = 0; i < number_of_vertices_; ++i) {
                for (size_t j = 0; j < number_of_vertices_; ++j) {
                    if (distance_[i][k] < INF && distance_[k][j] < INF) {
                        distance_[i][j] = std::min(distance_[i][j], distance_[i][k] + distance_[k][j]);
                    }
                }
            }
        }
    }

    size_t getDistance(size_t from, size_t to) const {
        return distance_[from][to];
    }

private:
    size_t number_of_vertices_;
    std::vector<std::vector<size_t>> distance_;

    static constexpr size_t INF = std::numeric_limits<int>::max() / 2;
};