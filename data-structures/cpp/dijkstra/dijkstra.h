#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <cstddef>
#include <limits>
#include <vector>

#include "../lib/assert_lib.h"

class dijkstra {
private:
    static constexpr double inf = std::numeric_limits<double>::max();

    int V{0};
    std::vector<std::vector<double>> adjMatrix;
    std::vector<std::vector<double>> distMatrix; // all-pairs shortest paths

    int minDistance(const std::vector<double>& dist, const std::vector<bool>& visited) const;

public:
    explicit dijkstra(const std::vector<std::vector<double>>& distTable);

    ~dijkstra() = default;

    // Single-source shortest paths from `src`.
    std::vector<double> calc(int src);

    // Fills `distMatrix` with all-pairs shortest paths.
    void calc();

    void print() const;

    const std::vector<std::vector<double>>& getDistMatrix() const { return distMatrix; }
    int size() const { return V; }
};


#endif // DIJKSTRA_H