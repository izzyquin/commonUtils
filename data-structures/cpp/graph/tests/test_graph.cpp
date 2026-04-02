/*  test functions to test the graph methods

    You can run the method using the command below:
        g++ -std=c++17 -o main testGraph.cpp -lgtest -lgtest_main -pthread
*/

#include "../graph.h"

#include <gtest/gtest.h>
#include <iostream>
#include <unordered_set>
#include <random>

class GraphTest: public ::testing::Test {
protected:
    
    Graph<double> g;

    void SetUp() override{}

    void TearDown() override{}
};

TEST_F(GraphTest, DFS_1) {
    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    std::vector<double> dfs = g.dfs(0);
    std::vector<double> exp1 = {0,1,3,5,4,2};
    std::vector<double> exp2 = {0,2,4,5,1,3}; // alternative DFS order

    EXPECT_EQ(dfs.size(), 6);
    EXPECT_TRUE(dfs == exp1 || dfs == exp2)
        << "DFS result did not match any expected order. Got: "
        << ::testing::PrintToString(dfs);
}

TEST_F(GraphTest, DFS_2) {
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(4, 6);

    std::vector<double> dfs = g.dfs(0);
    std::vector<double> exp1= {0,1,3,5,4,6,2};
    std::vector<double> exp2= {0,2,4,6,5,1,3};


    EXPECT_EQ(dfs.size(), 7);
    EXPECT_TRUE(dfs == exp1 || dfs == exp2)
        << "DFS result did not match any expected order. Got: "
        << ::testing::PrintToString(dfs);
}

TEST_F(GraphTest, BFS_1) {
    g.addEdge(0, 1);        
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    
    std::vector<double> bfs = g.bfs(0);
    std::vector<double> exp1= {0,1,2,3,4,5};
    std::vector<double> exp2= {0,2,1,4,3,5};

    EXPECT_EQ(bfs.size(), 6);
    EXPECT_TRUE(bfs == exp1 || bfs == exp2) 
        << "BFS result did not match any expected order. Got: "
        << ::testing::PrintToString(bfs);
}

TEST_F(GraphTest, BFS_2) {
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(4, 6);

    std::vector<double> bfs = g.bfs(0);
    std::vector<double> exp1= {0,1,2,3,4,5,6};
    std::vector<double> exp2= {0,2,1,4,3,6,5};

    EXPECT_EQ(bfs.size(), 7);
    EXPECT_TRUE(bfs == exp1 || bfs == exp2)
        << "BFS result did not match any expected order. Got: "
        << ::testing::PrintToString(bfs);
}

TEST_F(GraphTest, STRESS_LARGE_GRAPH) {
    const int N = 10000;       // number of nodes
    const int EDGES = 50000;   // number of edges

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, N - 1);

    // Build random graph
    for (int i = 0; i < EDGES; i++) {
        int u = dist(rng);
        int v = dist(rng);
        g.addEdge(u, v);
    }

    // Run traversals
    auto dfs = g.dfs(0);
    auto bfs = g.bfs(0);

    // ---- VALIDATION ----

    // 1. No duplicates
    std::unordered_set<double> dfs_set(dfs.begin(), dfs.end());
    std::unordered_set<double> bfs_set(bfs.begin(), bfs.end());

    EXPECT_EQ(dfs.size(), dfs_set.size())
        << "DFS contains duplicates";

    EXPECT_EQ(bfs.size(), bfs_set.size())
        << "BFS contains duplicates";

    // 2. DFS and BFS should visit same reachable nodes
    EXPECT_EQ(dfs_set, bfs_set)
        << "DFS and BFS visited different nodes";

    // 3. At least source node is present
    EXPECT_TRUE(dfs_set.count(0));
    EXPECT_TRUE(bfs_set.count(0));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
