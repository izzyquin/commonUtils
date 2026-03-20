#ifndef NODE_H
#define NODE_H

#include <vector>
#include "../lib/assert_lib.h"
#include "../lib/DataType.h"

class DataType;

class Node {
private:
    DataType    data;
    int         maxVertices;
    bool        _isVisited;
    std::vector<Node*> childList;

    // Declare friend class
    friend class graph;

public:

    Node(DataType* data, int max_vertices = 2);

    bool addChild(Node* v);

    int getNumberOfChild();

    DataType getData();

    bool isVisited();
    void setVisited(bool val);
};

#endif // NODE_H
