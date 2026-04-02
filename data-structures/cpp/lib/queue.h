#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "../lib/assert_lib.h"
#include "node.h"

template<typename T>
class Queue {
private:
    std::vector<T> items;
    int maxItems_;

public:
    Queue(int max_items = 10000) : maxItems_(max_items) {
            items.resize(max_items);
    }

    bool push(T& data) {
        ASSERT_RETURN(!isFull(), false);
        items.push_back(data);
        return true;
    }

    T pop() {
        if (isEmpty()) throw std::out_of_range("Queue is empty");
        T val= items.front();
        items.erase(items.begin());
        return val;
    }

    bool isEmpty() const {
        return items.empty();
    }

    bool isFull() const {
        return items.size() == maxItems_ - 1;
    }

    int  getLimit() const {
        return maxItems_;
    }

    void print() const {
        for (int i = 0 ; i <= items.size(); i++)
            std::cout << items[i] << " ";
        std::cout << "\n";
    }
};


#endif // QUEUE_H