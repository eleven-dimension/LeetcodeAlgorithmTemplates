#include <bits/stdc++.h>

template <class WeightType>
class FloydWarshall {
public:
    FloydWarshall(size_t number_of_vertices,
                  WeightType inf_weight = std::numeric_limits<WeightType>().max() / 2)
        : inf_weight_(inf_weight),
          distance_(number_of_vertices, std::vector<size_t>(number_of_vertices, inf_weight)) {
        for (size_t i = 0; i < number_of_vertices; ++i) {
            distance_[i][i] = 0;
        }
    }

    void addDirectedEdge(size_t from, size_t to, size_t weight) {
        distance_[from][to] = std::min(distance_[from][to], weight);
    }

    void addBidirectedEdge(size_t from, size_t to, size_t weight) {
        addDirectedEdge(from, to, weight);
        addDirectedEdge(to, from, weight);
    }

    void addEdge(size_t from, size_t to, size_t weight, bool bidirected) {
        (bidirected ? addBidirectedEdge : addDirectedEdge)(from, to, weight);
    }

    void computeShortestPaths() {
        const size_t num = number_of_vertices();
        for (size_t k = 0; k < num; ++k) {
            for (size_t i = 0; i < num; ++i) {
                for (size_t j = 0; j < num; ++j) {
                    distance_[i][j] = std::min(distance_[i][j], distance_[i][k] + distance_[k][j]);
                }
            }
        }
    }

    size_t getDistance(size_t from, size_t to) const {
        return distance_[from][to];
    }

private:
    size_t number_of_vertices() const {
        return distance_.size();
    }

    std::vector<std::vector<size_t>> distance_;

    const WeightType inf_weight_;
};
