cmake_minimum_required(VERSION 3.11)

project(GraphViewer C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# =============================================================================
# Project globals
# =============================================================================


include_directories(
    "include"
)

link_directories(
    "build"
)

add_subdirectory(deps/googletest)
add_subdirectory(deps/SDL)

# =============================================================================
# Utils .so
# =============================================================================


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

# =============================================================================
# Utils tests
# =============================================================================

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

# =============================================================================
# GraphViewer library
# =============================================================================

add_library(
    graph_viewer
    SHARED
    
    src/graph_viewer/graph.c
    src/graph_viewer/physics.c
)

set_target_properties(
    graph_viewer
    PROPERTIES
    LINKER_LANGUAGE C
)


# =============================================================================
# GraphViewer library tests
# =============================================================================

add_executable(
    gvlib_tests

    tests/graph_viewer/test_physics.cpp
)

target_link_libraries(
    gvlib_tests

    gtest_main
    gtest
    graph_viewer
    m
)

# =============================================================================
# GraphViewer App
# =============================================================================

add_executable(
    app 
    
    main.c
    src/app/draw.c
    src/app/sdl.c
)
target_link_libraries(
    app 
    
    graph_viewer
    SDL2-2.0
    m
)