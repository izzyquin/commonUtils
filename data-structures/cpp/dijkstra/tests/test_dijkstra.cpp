#include "../dijkstra.h"

#include <gtest/gtest.h>

#include <limits>
#include <vector>

namespace {
    constexpr double inf = std::numeric_limits<double>::max();

    std::vector<std::vector<double>> exampleGraph() {
        // Directed adjacency matrix representation.
        // inf means "no edge".
        return {
            {0, 2, inf, 1, inf},
            {2, 0, 4, inf, 5},
            {inf, 4, 0, 3, inf},
            {1, inf, 3, 0, 6},
            {inf, 5, inf, 6, 0},
        };
    }

    std::vector<std::vector<double>> unreachableGraph() {
        return {
            {0, 1, inf},
            {1, 0, inf},
            {inf, inf, 0},
        };
    }
} // namespace

TEST(DijkstraTest, SingleSourceFromZero) {
    dijkstra d(exampleGraph());
    const auto dist = d.calc(0);

    const std::vector<double> expected = {
        0, 2, 4, 1, 7,
    };

    ASSERT_EQ(dist.size(), expected.size());
    for (size_t i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(dist[i], expected[i], 1e-9);
    }
}

TEST(DijkstraTest, UnreachableVerticesAreinf) {
    dijkstra d(unreachableGraph());
    const auto dist = d.calc(0);

    const std::vector<double> expected = {
        0, 1, inf,
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
    EXPECT_EQ(dm[0][4], 7);
    EXPECT_EQ(dm[1][3], 3);
    EXPECT_EQ(dm[3][2], 3);
}

