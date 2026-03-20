#include <cstddef>
#include <map>
#include "../lib/assert_lib.h"
#include "stack.h"
#include "graph.h"

graph::graph(int max_node_child): _max_node_child(max_node_child) {}

Node* graph::find(DataType* key){
    auto it = vertex_storage.find(*key);
    if (it != vertex_storage.end())
    {
        return it->second;
    }
    return nullptr;
}

Node* graph::findNode(DataType* key, bool storeIfNotExist) {
    auto it = vertex_storage.find(*key);
    Node* node = nullptr;
    if (it == vertex_storage.end() && storeIfNotExist)
    {
        node = new Node(key);
        vertex_storage.insert(std::make_pair(*key, node));
    }
    else
    {
        node = it->second;
    }
    return node;
}

void graph::addEdge(DataType* src, DataType* dst) {
    ASSERT(src != nullptr);
    ASSERT(dst != nullptr);

    Node* src_node = findNode(src, true);
    Node* dst_node = findNode(dst, true);

    src_node->addChild(dst_node);
}

std::vector<DataType> graph::DFS_traverse(DataType* src)
{
    std::vector<DataType> rc;
    Node* src_node = findNode(src, false);
    ASSERT_RETURN(src_node != nullptr, rc);

    // reset visited vertices throughout the graph
    for (auto i = vertex_storage.begin(); i != vertex_storage.end(); i++) {
        i->second->setVisited(false);
    }

    Stack * st = new Stack();

    src_node->setVisited(true);
    st->push(src_node);
 
    while(!st->isEmpty())
    {
        Node* curr = st->pop();
        if (curr == nullptr) {
            continue;
        }

        curr->setVisited(true);
        rc.push_back(curr->getData());

        for (int i = 0; i < curr->getNumberOfChild(); i++)
        {
            int idx = curr->getNumberOfChild() - i - 1;
            Node* child = curr->childList[idx];
            if (!child->isVisited())
            {
                st->push(curr->childList[idx]);
            }
        }
    }

    delete st;
    return rc;
}

std::vector<DataType> graph::BFS_traverse(DataType* src)
{
    std::vector<DataType> rc;
    Node* src_node = findNode(src, false);
    ASSERT_RETURN(src_node != nullptr, rc);

    // reset visited vertices throughout the graph
    for (auto i = vertex_storage.begin(); i != vertex_storage.end(); i++) {
        i->second->setVisited(false);
    }

    Queue *q = new Queue();

    src_node->setVisited(true);
    q->push(src_node);

    while(!q->isEmpty())
    {
        Node* curr = q->pop();
        if (curr == nullptr) {
            continue;
        }

        rc.push_back(curr->getData());

        for (int i = 0; i < curr->getNumberOfChild(); i++)
        {
            //int idx = curr->getNumberOfChild() - i - 1;
            Node* child = curr->childList[i];
            if (!child->isVisited())
            {
                q->push(curr->childList[i]);
                curr->childList[i]->setVisited(true);
            }
        }
    }
    delete q;
    return rc;
}

void graph::print(const std::vector<DataType>& vec){
    ASSERT(!vec.empty());
    std::cout << vec[0];
    for (std::size_t i = 1; i < vec.size(); i++) {
        std::cout << "," << vec[i];
    }
    std::cout << std::endl;
}

graph::~graph(){
    for (auto i = vertex_storage.begin(); i != vertex_storage.end(); i++) {
        delete i->second;
    }
}


