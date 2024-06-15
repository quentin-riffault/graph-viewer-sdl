cmake_minimum_required(VERSION 3.11)

project(GraphViewer C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
    "include"
)

link_directories(
    "build"
)

add_library(
    gv_utils
    SHARED
    
    src/utils/hash_map.c
)

set_target_properties(
    gv_utils
    PROPERTIES
    LINKER_LANGUAGE C
)

add_executable(
    gv_utils_tests

    tests/utils/test_hash_map.cpp
)

target_link_libraries(
    gv_utils_tests

    gtest_main
    gtest
    gv_utils
)
