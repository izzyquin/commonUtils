#include "queue.h"

Queue::Queue(int max_items) : _maxItems(max_items) {}

bool Queue::isEmpty() {
    return items.size() == 0;
}

bool Queue::isFull() {
    return items.size() >= static_cast<std::size_t>(_maxItems);
}

bool Queue::push(Node* data) {
    ASSERT_RETURN(!isFull(), false);
    items.push_back(data);
    return true;
}

Node* Queue::pop() {
    ASSERT_RETURN(!isEmpty(), nullptr);

    Node* rc = items.front();
    items.erase(items.begin());
    return rc;
}

int Queue::getLimit() {
    return _maxItems;
}

void Queue::print() const
{
    std::cout << "Queue"<< std::endl;
    std::cout << "---------"<< std::endl;
    for (int i = static_cast<int>(items.size()) - 1 ; i >= 0; i--)
    {
        std::cout << "| "<<items[i]->getData()<<" |"<<std::endl;
    }
    std::cout << "---------"<<std::endl;
}
