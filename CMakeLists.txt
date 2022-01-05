cmake_minimum_required(VERSION 3.20)
project(GraphColoring)

include_directories(/home/danny/Personal/C++/boost_1_66_0)
set(CMAKE_CXX_STANDARD 17)

add_executable(GraphColoring main.cpp Graph.h Node.h)
