
#include "TrieNode.h"
#include <string_view>

void TrieNode::insert(std::string_view word) {
    if (!isValidWord(word)) {
        return;
    }

    Node* current = root_.get();
    for (char c : word) {
        const std::size_t index = static_cast<std::size_t>(c - 'a');
        auto& child = current->children[index];
        if (!child) {
            child = std::make_unique<Node>();
        }
        current = child.get();
    }
    current->is_end_of_word = true;
}

bool TrieNode::search(std::string_view word) const noexcept {
    if (!isValidWord(word)) {
        return false;
    }

    const Node* current = root_.get();
    for (char c : word) {
        const std::size_t index = static_cast<std::size_t>(c - 'a');
        const auto& child = current->children[index];
        if (!child) {
            return false;
        }
        current = child.get();
    }
    return current->is_end_of_word;
}

