#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <iostream>
#include "Graph.h"

int main() {
    Graph g("../examples/input_file.txt");

    std::cout << "Number of unique colors: " << g.getNumColorsUsed();

    g.exportToDot("output.txt");


    return 0;
}