#pragma once

#include <array>
#include <cstddef>
#include <memory>
#include <string_view>

// A minimal Trie for lowercase [a-z] words.
// "End of word" is tracked so prefix queries return false unless the full word was inserted.
class TrieNode {
private:
    static constexpr std::size_t ALPHABET_CHARS = 26;
    static constexpr std::size_t MAX_WORD_LENGTH = 100; // Reject length >= MAX_WORD_LENGTH.

    struct Node {
        std::array<std::unique_ptr<Node>, ALPHABET_CHARS> children{};
        bool is_end_of_word = false;
    };

    std::unique_ptr<Node> root_ = std::make_unique<Node>();

    static bool isValidWord(std::string_view word) noexcept {
        if (word.empty() || word.size() >= MAX_WORD_LENGTH) {
            return false;
        }
        for (char c : word) {
            if (c < 'a' || c > 'z') {
                return false;
            }
        }
        return true;
    }

public:
    TrieNode() = default;
    TrieNode(const TrieNode&) = delete;
    TrieNode& operator=(const TrieNode&) = delete;
    TrieNode(TrieNode&&) noexcept = default;
    TrieNode& operator=(TrieNode&&) noexcept = default;

    void insert(std::string_view word);
    [[nodiscard]] bool search(std::string_view word) const noexcept;

    void clear() noexcept {
        root_ = std::make_unique<Node>();
    }
};
