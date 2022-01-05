#include <iostream>
#include "Graph.h"

int main() {
    Graph g("../examples/input_file.txt");
    Graph g2(g);
    g.exportToDot("output.txt");
    g2.exportToDot("output2.txt");
    return 0;
}