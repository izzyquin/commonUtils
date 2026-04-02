#include "./dijkstra.h"

#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
    constexpr int INVALID_IDX = -1;
}

dijkstra::dijkstra(const std::vector<std::vector<double>>& distTable)
    : V(static_cast<int>(distTable.size())),
      adjMatrix(distTable),
      distMatrix(V, std::vector<double>(V, inf)) {
    if (V <= 0) {
        throw std::invalid_argument("dijkstra: adjacency matrix must be non-empty");
    }

    for (const auto& row : adjMatrix) {
        if (static_cast<int>(row.size()) != V) {
            throw std::invalid_argument("dijkstra: adjacency matrix must be square");
        }
    }

    // Dijkstra requires non-negative edge weights.
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            const double w = adjMatrix[i][j];
            if (w != inf && w < 0) {
                throw std::invalid_argument("dijkstra: negative edge weights are not supported");
            }
        }
    }
}

int dijkstra::minDistance(const std::vector<double>& dist, const std::vector<bool>& visited) const {
    ASSERT_RETURN(static_cast<int>(dist.size()) == V, INVALID_IDX);
    ASSERT_RETURN(static_cast<int>(visited.size()) == V, INVALID_IDX);

    int index = INVALID_IDX;
    double min_val = inf;

    for (int i = 0; i < V; i++) {
        const double di = dist[i];
        if (!visited[i] && di <= min_val) {
            min_val = di;
            index = i;
        }
    }
    return index;
}

std::vector<double> dijkstra::calc(int src) {
    ASSERT_RETURN(src >= 0 && src < V, std::vector<double>{});

    std::vector<bool> visited(V, false);
    std::vector<double> dist(V, inf);
    dist[src] = 0;

    for (int count = 0; count < V; count++) {
        const int u = minDistance(dist, visited);
        if (u == INVALID_IDX || dist[u] == inf) {
            break; // no reachable remaining vertices
        }

        visited[u] = true;
        for (int v = 0; v < V; v++) {
            if (visited[v]) continue;

            double w = adjMatrix[u][v];
            if (w == inf)  continue; // no edge

            double du = dist[u];
            if (du == inf) continue;

            double cand = du + w;
            if (cand < dist[v]) {
                dist[v] = cand;
            }
        }
    }

    return dist;
}

void dijkstra::calc(){
	for (int i = 0; i < V; i++)
	{	
		distMatrix[i] = calc(i);
	}
}

void dijkstra::print() const {
    for (int i = -1; i < V; i++) {
        if (i < 0) {
            std::cout << "D" << "\t";
        } else {
            std::cout << i << "\t";
        }

        for (int j = 0; j < V; j++) {
            if (i < 0) {
                std::cout << j << "\t";
                continue;
            }
            std::cout << distMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
