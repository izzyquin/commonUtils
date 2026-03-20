#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <cstddef>
#include <limits>
#include <vector>

#include "../lib/DataType.h"
#include "../lib/assert_lib.h"

class dijkstra {
private:
    static constexpr int INF = std::numeric_limits<int>::max();

    int V{0};
    std::vector<std::vector<DataType>> adjMatrix;
    std::vector<std::vector<DataType>> distMatrix; // all-pairs shortest paths

    int minDistance(const std::vector<DataType>& dist, const std::vector<bool>& visited) const;

public:
    explicit dijkstra(const std::vector<std::vector<DataType>>& distTable);
    ~dijkstra() = default;

    // Single-source shortest paths from `src`.
    std::vector<DataType> calc(int src);

    // Fills `distMatrix` with all-pairs shortest paths.
    void calc();

    void print() const;

    const std::vector<std::vector<DataType>>& getDistMatrix() const { return distMatrix; }
    int size() const { return V; }
};

#endif // DIJKSTRA_H