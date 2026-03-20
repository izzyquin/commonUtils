#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include "../lib/assert_lib.h"
#include "stack.h"
#include "queue.h"

class graph {
private:
    int _max_node_child;
    std::map<DataType, Node*> vertex_storage;

public:
    graph(int max_node_child = 2);
    
    ~graph();

    Node* find(DataType* key);

    Node* findNode(DataType* key, bool storeIfNotExist);

    void addEdge(DataType* src, DataType* dst);

    std::vector<DataType> DFS_traverse(DataType* src);

    std::vector<DataType> BFS_traverse(DataType* src);

    static void print(const std::vector<DataType>& vec);
};

#endif // QRAPH_H