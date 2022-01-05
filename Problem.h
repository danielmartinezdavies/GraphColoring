//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_PROBLEM_H
#define GRAPHCOLORING_PROBLEM_H
#include "Graph.h"

class Problem{
    std::vector<Graph> graph_list;
    const std::vector<std::string> color_list{"red", "blue", "yellow"};
public:
    Problem(std::string input_file, int size){
        Graph g1(input_file, color_list);
        graph_list.push_back(g1);
        for(int i = 1; i < size; i++){
            graph_list.emplace_back(g1);
        }
        for(int i = 0; i < size; i++){
            std::string filename = "output" + std::to_string(i);
            graph_list[i].exportToDot(filename);
        }
    }
};

#endif //GRAPHCOLORING_PROBLEM_H
