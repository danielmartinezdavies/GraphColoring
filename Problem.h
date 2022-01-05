//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_PROBLEM_H
#define GRAPHCOLORING_PROBLEM_H
#include "Graph.h"

class Problem{
    std::vector<Graph> graph_list;
    const std::vector<std::string> color_list{"red", "blue", "yellow", "green", "black"};
public:
    Problem(const std::string &input_file, int size){
        Graph g1(input_file, color_list);
        graph_list.push_back(g1);
        for(int i = 1; i < size; i++){
            Graph g2(g1);
            g2.colorGraph(color_list);
            graph_list.emplace_back(g2);
        }

    }

    void generateSimulations(int num_gen){
        std::unique_ptr<Graph> best_graph = getBestGraph();
        for(int i = 0; i < num_gen; i++){
            std::cout << "Generation: " << i << "\n";
            std::cout << "Best fitness found: " << best_graph->getFitness() << std::endl;
            if(getBestGraph()->getFitness() < best_graph->getFitness())
                best_graph = getBestGraph();
        }
        std::cout << "Finished " << num_gen << " generations \n";
        std::cout << "Best fitness found: " << best_graph->getFitness() << std::endl;

        best_graph->exportToDot("best_solution_found.txt");

    }

    void exportPopulationToFile(){
        for(int i = 0; i < graph_list.size(); i++){
            std::string filename = "output" + std::to_string(i);
            graph_list[i].exportToDot(filename);
        }
    }

    std::unique_ptr<Graph> getBestGraph(){
        auto best_graph = std::make_unique<Graph>(graph_list[0]);
        for(auto graph : graph_list){
            if(graph.getFitness() < best_graph->getFitness())
                best_graph = std::make_unique<Graph>(graph);
        }
        return best_graph;
    }
    void crossOverPopulation(std::vector<Graph> parent_list){
        for(int i = 0; i < parent_list.size(); i++){
            std::uniform_int_distribution<std::mt19937::result_type> dist(0,parent_list.size()-1);
            Graph father = parent_list[dist(rng)];
            Graph mother = parent_list[dist(rng)];
        }
    }

    void mutatePopulation(int prob){
        for(auto graph : graph_list){
            graph.mutate(prob);
        }
    }
};

#endif //GRAPHCOLORING_PROBLEM_H
