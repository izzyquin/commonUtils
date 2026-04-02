#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_set>
#include <vector>
#include "../lib/assert_lib.h"
#include "../lib/node.h"

template<typename T>
class Graph {
private:
    std::map<T, std::unique_ptr<Node<T>>> vertex_storage;

    Node<T>* findNode(const T& key) {
        auto it = vertex_storage.find(key);
        return (it != vertex_storage.end()) ? it->second.get() : nullptr;
    }

    Node<T>* GetOrCreateNode(const T& key) {
        auto it = vertex_storage.find(key);

        if (it == vertex_storage.end()) {
            auto node = std::make_unique<Node<T>>(key);
            auto raw_ptr = node.get();
            vertex_storage.insert({key, std::move(node)});
            return raw_ptr;
        }

        return it->second.get();
    }

public:
    Graph() = default;
    
    ~Graph() = default;

    void addEdge(const T& src, const T& dst)  {
        auto src_node = GetOrCreateNode(src);
        auto dst_node = GetOrCreateNode(dst);

        src_node->addChild(dst_node);
    }

    std::vector<T> dfs(const T& src) {
        std::vector<T> rv;

        auto src_node = findNode(src);
        if (!src_node) return rv;

        std::stack<Node<T>*> nodes;
        std::unordered_set<Node<T>*> visited;

        nodes.push(src_node);
        visited.insert(src_node);

        while (!nodes.empty()) {
            auto curr = nodes.top();
            nodes.pop();

            rv.push_back(curr->getData());

            for (auto child : curr->getChildren()) {
                if (!visited.count(child)) {
                    visited.insert(child);
                    nodes.push(child);
                }
            }
        }

        return rv;
    }

    std::vector<T> bfs(const T& src) {
        std::vector<T> rv;

        auto src_node = findNode(src);
        if (!src_node) return rv;

        std::unordered_set<Node<T>*> visited;
        std::queue<Node<T>*> nodes;

        visited.insert(src_node);
        nodes.push(src_node);

        while(!nodes.empty()) {
            auto curr = nodes.front();
            nodes.pop();

            rv.push_back(curr->getData());

            for (auto child : curr->getChildren()) {
                if (!visited.count(child)) {
                    visited.insert(child);
                    nodes.push(child);
                }
            }
        }

        return rv;
    }

    static void print(const std::vector<T>& vec) {
        if (vec.empty()) return;

        std::cout << vec[0];
        for (std::size_t i = 1; i < vec.size(); i++) {
            std::cout << "," << vec[i];
        }
        std::cout << "\n";
    }
};

#endif // GRAPH_H