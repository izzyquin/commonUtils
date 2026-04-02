add_executable(graph_tests
   tests/test_graph.cpp
)

target_compile_features(graph_tests PRIVATE cxx_std_20)
target_link_libraries(graph_tests PRIVATE GTest::gtest GTest::gtest_main)
target_include_directories(graph_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
add_test(NAME graph_tests COMMAND graph_tests)
