#ifndef NODE_H
#define NODE_H

#include <vector>
#include "../lib/assert_lib.h"

template<typename T>
class Node {
private:
    T data;
    std::vector<Node<T>*> childList;

public:

    Node(const T& val) : data(val) {}

    T getData() const { return data; }

    void addChild(Node<T>* child) { childList.push_back(child); }
    int getNumberOfChild() const { return childList.size(); }
    const std::vector<Node<T>*>& getChildren(){ return childList; }
};

#endif // NODE_H
