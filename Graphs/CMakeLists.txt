cmake_minimum_required(VERSION 3.16)
project(graphs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES Graph.cpp Vertex.cpp)
set(HEADERS Graph.h Vertex.h)

add_library(graphs STATIC ${SOURCES})
target_include_directories(graphs PUBLIC .)

