#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "../lib/assert_lib.h"
#include "node.h"

class DataType;

class Stack {
private:
    std::vector<Node*> items;
    int     top;
    int     _maxItems;

public:
    Stack(int max_items = 10);

    bool  push(Node* data);
    Node* pop();

    bool isEmpty();
    bool isFull();
    int  getLimit();
    void print() const;
};

#endif // STACK_H