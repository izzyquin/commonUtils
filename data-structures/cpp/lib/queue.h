#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "../lib/assert_lib.h"
#include "node.h"

class DataType;

class Queue {
private:
    std::vector<Node*> items;
    int     top;
    int     _maxItems;

public:
    Queue(int max_items = 10);

    bool  push(Node* data);
    Node* pop();

    bool isEmpty();
    bool isFull();
    int  getLimit();
    void print() const;
};

#endif // QUEUE_H