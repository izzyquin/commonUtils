cmake_minimum_required(VERSION 3.20)

project(data_structures_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

# Check GTest once at this parent level.
find_package(GTest REQUIRED)

add_subdirectory(graph)
add_subdirectory(Trie)
add_subdirectory(dijkstra)
