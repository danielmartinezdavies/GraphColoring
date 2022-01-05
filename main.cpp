#include "Graph.h"

int main() {
    const std::vector<std::string> color_list{"red", "blue", "yellow"};
    Graph g("../examples/input_file.txt", color_list);
    Graph g2(g);
    g.exportToDot("output.txt");
    g2.exportToDot("output2.txt");
    return 0;
}