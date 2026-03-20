#include "node.h"

Node::Node(DataType* data, int max_vertices)
    : data(*data), maxVertices(max_vertices) {
    ASSERT(data != nullptr);
    _isVisited = false;
}

bool Node::addChild(Node* v) {
    ASSERT_RETURN(childList.size() < maxVertices, false);
    childList.push_back(v);
    return true;
}

int Node::getNumberOfChild() {
    return static_cast<int>(childList.size());
}

DataType Node::getData() {
    return data;
}

bool Node::isVisited() {
    return _isVisited;
}

void Node::setVisited(bool val) {
    _isVisited = val;
}
