#include <bits/stdc++.h>

class FloydWarshall {
public:
    FloydWarshall(int number_of_vertices) 
        : number_of_vertices_(number_of_vertices), 
          distance_(number_of_vertices, std::vector<int>(number_of_vertices, INF)) {
        for (int i = 0; i < number_of_vertices; ++i) {
            distance_[i][i] = 0;
        }
    }

    void addEdge(int from, int to, int weight) {
        distance_[from][to] = std::min(distance_[from][to], weight);
        distance_[to][from] = std::min(distance_[to][from], weight);
    }

    void computeShortestPaths() {
        for (int k = 0; k < number_of_vertices_; ++k) {
            for (int i = 0; i < number_of_vertices_; ++i) {
                for (int j = 0; j < number_of_vertices_; ++j) {
                    if (distance_[i][k] < INF && distance_[k][j] < INF) {
                        distance_[i][j] = std::min(distance_[i][j], distance_[i][k] + distance_[k][j]);
                    }
                }
            }
        }
    }

    int getDistance(int from, int to) const {
        return distance_[from][to];
    }

private:
    int number_of_vertices_;
    std::vector<std::vector<int>> distance_;

    static constexpr int INF = std::numeric_limits<int>::max() / 2;
};