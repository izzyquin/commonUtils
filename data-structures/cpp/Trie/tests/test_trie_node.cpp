/* Unit tests for TrieNode.
 *
 * Compile/run example (from `testTrieNode.sh`):
 *   g++ -std=c++20 -o main testTrieNode.cpp TrieNode.cpp -lgtest -lgtest_main -pthread
 */

#include "../TrieNode.h"

#include <gtest/gtest.h>

#include <string>

TEST(TrieNodeTest, SearchBeforeInsertIsFalse) {
    TrieNode trie;
    EXPECT_FALSE(trie.search("apple"));
}

TEST(TrieNodeTest, InsertsAndFindsWholeWordOnly) {
    TrieNode trie;
    trie.insert("apple");

    EXPECT_FALSE(trie.search(" "));
    EXPECT_TRUE(trie.search("apple"));
    EXPECT_FALSE(trie.search("app"));   // prefix, not a full word
    EXPECT_FALSE(trie.search("orange"));
}

TEST(TrieNodeTest, MultipleWordsAndPrefixes) {
    TrieNode trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");

    EXPECT_TRUE(trie.search("app"));
    EXPECT_TRUE(trie.search("apple"));
    EXPECT_TRUE(trie.search("banana"));
    EXPECT_FALSE(trie.search("ban"));  // prefix, not a full word
}

TEST(TrieNodeTest, DuplicateInsertIsIdempotent) {
    TrieNode trie;
    trie.insert("apple");
    trie.insert("apple");
    EXPECT_TRUE(trie.search("apple"));
}

TEST(TrieNodeTest, EmptyStringIsRejected) {
    TrieNode trie;
    trie.insert("");
    EXPECT_FALSE(trie.search(""));
}

TEST(TrieNodeTest, InvalidCharactersAreRejected) {
    TrieNode trie;

    EXPECT_FALSE(trie.search(" "));   // space not in [a-z]
    EXPECT_FALSE(trie.search("app1")); // digit not in [a-z]

    trie.insert("app1");
    EXPECT_FALSE(trie.search("app1"));
}

TEST(TrieNodeTest, UppercaseWordsAreRejected) {
    TrieNode trie;
    trie.insert("Apple");
    EXPECT_FALSE(trie.search("Apple"));
    EXPECT_FALSE(trie.search("apple")); // never inserted
}

TEST(TrieNodeTest, LengthBoundary99Allowed_100Rejected) {
    TrieNode trie;

    std::string len99(99, 'a');
    std::string len100(100, 'a');

    trie.insert(len99);
    EXPECT_TRUE(trie.search(len99));

    trie.insert(len100); // rejected (>= MAX_WORD_LENGTH)
    EXPECT_FALSE(trie.search(len100));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

