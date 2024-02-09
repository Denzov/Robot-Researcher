cmake_minimum_required(VERSION 3.16)
project(graphs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES Graph.cpp Graph.h)

set_target_properties(raylib PROPERTIES
                    graphs Graph.h)

#target_include_directories(graphs PUBLIC Graph.h)

add_library(graphs ${SOURCES} Graph.h)
