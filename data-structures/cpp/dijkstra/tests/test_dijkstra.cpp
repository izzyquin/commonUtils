#include "../Dijkstra.h"

#include <gtest/gtest.h>

#include <limits>
#include <vector>

namespace {
    constexpr int INF = std::numeric_limits<int>::max();

    std::vector<std::vector<DataType>> exampleGraph() {
        // Directed adjacency matrix representation.
        // INF means "no edge".
        return {
            {0, 2, INF, 1, INF},
            {2, 0, 4, INF, 5},
            {INF, 4, 0, 3, INF},
            {1, INF, 3, 0, 6},
            {INF, 5, INF, 6, 0},
        };
    }

    std::vector<std::vector<DataType>> unreachableGraph() {
        return {
            {0, 1, INF},
            {1, 0, INF},
            {INF, INF, 0},
        };
    }
} // namespace

TEST(DijkstraTest, SingleSourceFromZero) {
    dijkstra d(exampleGraph());
    const auto dist = d.calc(0);

    const std::vector<DataType> expected = {
        DataType(0), DataType(2), DataType(4), DataType(1), DataType(7),
    };

    ASSERT_EQ(dist.size(), expected.size());
    for (size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(dist[i], expected[i]);
    }
}

TEST(DijkstraTest, UnreachableVerticesAreInf) {
    dijkstra d(unreachableGraph());
    const auto dist = d.calc(0);

    const std::vector<DataType> expected = {
        DataType(0), DataType(1), DataType(INF),
    };

    ASSERT_EQ(dist.size(), expected.size());
    for (size_t i = 0; i < expected.size(); i++) {
        EXPECT_EQ(dist[i], expected[i]);
    }
}

TEST(DijkstraTest, CalcComputesAllPairs) {
    dijkstra d(exampleGraph());
    d.calc();

    const auto& dm = d.getDistMatrix();
    EXPECT_EQ(dm.size(), static_cast<size_t>(d.size()));
    EXPECT_EQ(dm[0][4], DataType(7));
    EXPECT_EQ(dm[1][3], DataType(3));
    EXPECT_EQ(dm[3][2], DataType(3));
}

