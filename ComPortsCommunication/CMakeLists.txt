cmake_minimum_required(VERSION 3.16)
project(Communications)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES *.cpp)

add_executable(Communications main.cpp comPortCommunication.cpp)