#include "Dijkstra.h"

#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
    constexpr int INVALID_IDX = -1;
}

dijkstra::dijkstra(const std::vector<std::vector<DataType>>& distTable)
    : V(static_cast<int>(distTable.size())),
      adjMatrix(distTable),
      distMatrix(static_cast<int>(distTable.size()),
                  std::vector<DataType>(static_cast<int>(distTable.size()), DataType(INF))) {
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
            const int w = adjMatrix[i][j].getData();
            if (w != INF && w < 0) {
                throw std::invalid_argument("dijkstra: negative edge weights are not supported");
            }
        }
    }
}

int dijkstra::minDistance(const std::vector<DataType>& dist, const std::vector<bool>& visited) const {
    ASSERT_RETURN(static_cast<int>(dist.size()) == V, INVALID_IDX);
    ASSERT_RETURN(static_cast<int>(visited.size()) == V, INVALID_IDX);

    int index = INVALID_IDX;
    int min_val = INF;

    for (int i = 0; i < V; i++) {
        const int di = dist[i].getData();
        if (!visited[i] && di <= min_val) {
            min_val = di;
            index = i;
        }
    }
    return index;
}

std::vector<DataType> dijkstra::calc(int src) {
    ASSERT_RETURN(src >= 0 && src < V, std::vector<DataType>{});

    std::vector<bool> visited(V, false);
    std::vector<DataType> dist(V, DataType(INF));
    dist[src] = DataType(0);

    for (int count = 0; count < V; count++) {
        const int u = minDistance(dist, visited);
        if (u == INVALID_IDX || dist[u].getData() == INF) {
            break; // no reachable remaining vertices
        }

        visited[u] = true;
        for (int v = 0; v < V; v++) {
            if (visited[v]) {
                continue;
            }

            const int w = adjMatrix[u][v].getData();
            if (w == INF) {
                continue; // no edge
            }

            const int du = dist[u].getData();
            if (du == INF) {
                continue;
            }

            const long long cand_ll = static_cast<long long>(du) + static_cast<long long>(w);
            const int cand = (cand_ll > INF) ? INF : static_cast<int>(cand_ll);
            if (cand < dist[v].getData()) {
                dist[v] = DataType(cand);
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
            std::cout << distMatrix[i][j].getData() << "\t";
        }
        std::cout << std::endl;
    }
}



