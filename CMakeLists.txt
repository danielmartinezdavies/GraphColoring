cmake_minimum_required(VERSION 3.16)
project(GraphColoring)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS regex graph )
include_directories(${Boost_INCLUDE_DIR} )
add_executable(GraphColoring main.cpp Graph.h Node.h Problem.h Parameters.h ColoredNode.h ColoredGraph.h)
target_link_libraries(GraphColoring ${Boost_LIBRARIES} )

enable_testing()
add_subdirectory(testing)