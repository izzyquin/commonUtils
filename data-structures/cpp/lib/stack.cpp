#include "stack.h"

Stack::Stack(int max_items) : _maxItems(max_items) {}

bool Stack::isEmpty() {
    return items.size() == 0;
}

bool Stack::isFull() {
    return items.size() >= static_cast<std::size_t>(_maxItems);
}

bool Stack::push(Node* data) {
    ASSERT_RETURN(!isFull(), false);
    items.push_back(data);
    return true;
}

Node* Stack::pop() {
    ASSERT_RETURN(!isEmpty(), nullptr);

    Node* rc = items.back();
    items.pop_back();
    return rc;
}

int Stack::getLimit() {
    return _maxItems;
}

void Stack::print() const
{
    std::cout << "STACK"<< std::endl;
    std::cout << "---------"<< std::endl;
    for (int i = static_cast<int>(items.size()) - 1 ; i >= 0; i--)
    {
        std::cout << "| "<<items[i]->getData()<<" |"<<std::endl;
    }
    std::cout << "---------"<<std::endl;
}
