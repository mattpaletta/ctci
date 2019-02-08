project("CTCI")
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_PYTHON "Build Python SWIG module" ON)

if (BUILD_PYTHON)
    add_subdirectory(python)
endif()

add_subdirectory("linked_list")
add_subdirectory("convex_hull")
add_subdirectory("binary_tree")
add_subdirectory("tower_of_hanoi")
## Setup testing
#include(cmake/googletest.cmake)
#fetch_googletest(
#        ${PROJECT_SOURCE_DIR}/cmake
#        ${PROJECT_BINARY_DIR}/googletest
#)
#enable_testing()
#add_subdirectory(tests)