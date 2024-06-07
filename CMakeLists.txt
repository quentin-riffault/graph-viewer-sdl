cmake_minimum_required(VERSION 3.11)

project(GraphViewer C)

include(FetchContent)
FetchContent_Declare(
    libsdl
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG     release-2.30.3
)

FetchContent_MakeAvailable(libsdl)

set(LIBSDL_INCLUDE PRIVATE "build/deps/libsdl-build/include/")
###############################################################################
# LibGraphViewer

add_library(GraphViewer SHARED src/graph_sdl.c)
target_include_directories(GraphViewer PUBLIC "include" ${LIBSDL_INCLUDE})

###############################################################################
# TestGraphViewer

add_executable(TestGraphViewer main.c)
target_include_directories(TestGraphViewer PUBLIC "include" ${LIBSDL_INCLUDE})
target_link_libraries(TestGraphViewer PUBLIC GraphViewer SDL2-2.0)