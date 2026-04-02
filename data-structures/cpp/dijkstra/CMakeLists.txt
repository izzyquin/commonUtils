add_executable(dijkstra_tests
    dijkstra.cpp
    tests/test_dijkstra.cpp
)

target_compile_features(dijkstra_tests PRIVATE cxx_std_20)
target_link_libraries(dijkstra_tests PRIVATE GTest::gtest GTest::gtest_main)
target_include_directories(dijkstra_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
add_test(NAME dijkstra_tests COMMAND dijkstra_tests)

