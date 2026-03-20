add_executable(trie_tests
    TrieNode.cpp
    tests/test_trie_node.cpp
)

target_compile_features(trie_tests PRIVATE cxx_std_20)
target_link_libraries(trie_tests PRIVATE GTest::gtest GTest::gtest_main)
target_include_directories(trie_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME trie_tests COMMAND trie_tests)
