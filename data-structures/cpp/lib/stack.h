#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "../lib/assert_lib.h"
#include "node.h"

template<typename T>
class Stack {
private:
    std::vector<T> items;
    int top;
    int maxItems_;

public:
    Stack(int max_items = 10000)
    : maxItems_(max_items) {}

    bool push(T& data) {
        ASSERT_RETURN(!isFull(), false);
        items.push_back(data);
        return true;
    }

    T pop() {
        if (isEmpty()) throw std::out_of_range("Stack is empty");

        T rc = items.back();
        items.pop_back();
        return rc;
    }

    bool isEmpty() { return items.size() == 0; }

    bool isFull() { return items.size() >= maxItems_; }

    int  getLimit() { return maxItems_; }

    void print() const {
        for (int i = 0 ; i <= top; i++)
            std::cout << items[i] << " ";
        std::cout << "\n";
    }
};


#endif // STACK_H