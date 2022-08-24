//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_PROBLEM_H
#define GRAPHCOLORING_PROBLEM_H
#include "Graph.h"
#include "boost/graph/sequential_vertex_coloring.hpp"

class Problem{
    std::vector<Graph> graph_list;
    std::vector<std::string> color_list;

    const int mutation_prob = 1000;
    const int tournament_size = 2;
    const bool replace_old_generation = true;

public:
    Problem(const std::string &input_file, int size, int mutation_prob, int tournament_size, bool replace_old_generation): mutation_prob(mutation_prob), tournament_size(tournament_size), replace_old_generation(replace_old_generation){
        Graph g1(input_file);

        for(int i = 0; i < g1.NodeList.size(); i++){
            color_list.emplace_back(generate_hex_color_code());
        }
        g1.colorGraph(color_list);
        graph_list.push_back(g1);


        for(int i = 1; i < size; i++){
            Graph g2(g1);
            g2.colorGraph(color_list);
            graph_list.push_back(g2);
        }

        getGreedyFitness(g1);
    }

    void getGreedyFitness(const Graph &g1){
        Graph g3(g1);
        g3.colorGraphGreedy(color_list);
        //std::cout << "Greedy fitness: " << g3.getFitness() << std::endl;
    }

    std::string generate_hex_color_code(){
        std::string hex = "#000000";
        char hex_char[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        for(int i = 1; i < 7; i++){
            std::uniform_int_distribution<std::mt19937::result_type> dist(0,15);
            hex[i]=hex_char[dist(rng)];
        }
        return hex;
    }

    std::string generateSimulations(int num_gen, int run_num, bool disable_printing){
        std::shared_ptr<Graph> best_graph = getBestGraph();
        std::string csv = "";
        if(!disable_printing) {
            std::cout << "Best fitness found: " << best_graph->getFitness() << std::endl;
           csv = "Generation;Best_Fitness\n";
        }
        int num_gens_since_improve = 0;
        for(int i = 0; true; i++){
            if(num_gens_since_improve > num_gen) break;
            csv += std::to_string(i) + ";" + std::to_string(best_graph->getFitness()) + "\n";
            if(!disable_printing) std::cout << "Generation: " << i << "\n";
            if(getBestGraph()->getFitness() < best_graph->getFitness()) {
                best_graph = getBestGraph();
                if(!disable_printing) std::cout << "New best fitness found: " << best_graph->getFitness() << std::endl;
                num_gens_since_improve = 0;
            }

            std::vector<Graph> parent_list = selectParentList(tournament_size);
            std::vector<Graph> child_list = crossOverPopulation(parent_list);
            mutatePopulation(mutation_prob, color_list);
            selectNextGeneration(child_list, replace_old_generation);
            num_gens_since_improve++;
        }
        if(!disable_printing) std::cout << "Finished " << num_gen << " generations \n";
        std::cout << "Best fitness found: " << best_graph->getFitness() << std::endl;

        std::string file = "best_solution_found_" + std::to_string(run_num) + ".txt";
        best_graph->exportToDot(file);
        return csv;
    }

    void exportPopulationToFile(){
        for(int i = 0; i < graph_list.size(); i++){
            std::string filename = "output" + std::to_string(i);
            graph_list[i].exportToDot(filename);
        }
    }

    std::shared_ptr<Graph> getBestGraph(){
        auto best_graph = std::make_shared<Graph>(graph_list[0]);
        for(auto graph : graph_list){
            if(graph.getFitness() < best_graph->getFitness())
                best_graph = std::make_shared<Graph>(graph);
        }
        return best_graph;
    }
    std::vector<Graph> selectParentList(int tournament_s){
        std::vector<Graph> parent_list;
        for(int i = 0; i < graph_list.size(); i++){
            std::vector<unsigned long> tournament_list;
            for(int j = 0; j < tournament_s; j++){
                std::uniform_int_distribution<std::mt19937::result_type> dist(0,graph_list.size()-1);
                tournament_list.push_back(dist(rng));
            }
            unsigned long best_graph = tournament_list[0];
            for(int j = 0; j < tournament_s; j++){
                if(graph_list[tournament_list[j]].getFitness() < graph_list[best_graph].getFitness())
                    best_graph = tournament_list[j];
            }
            parent_list.push_back(graph_list[best_graph]);
        }
        return parent_list;
    }

    std::vector<Graph> crossOverPopulation(std::vector<Graph> parent_list){
        std::vector<Graph> child_list;
        for(int i = 0; i < parent_list.size(); i++){
            std::uniform_int_distribution<std::mt19937::result_type> dist(0,parent_list.size()-1);
            Graph father = parent_list[dist(rng)];
            Graph mother = parent_list[dist(rng)];
            Graph child(father);
            child.colorGraphEmpty();
            child.crossOver(father, mother, color_list);
            child_list.emplace_back(child);
        }
        return child_list;
    }

    void mutatePopulation(int prob, const std::vector<std::string> &color_list){
        for(auto graph : graph_list){
            graph.mutate(prob, color_list);
        }
    }

    void selectNextGeneration(const std::vector<Graph> &child_list, bool replace_old_generation){
        if(replace_old_generation) {
            graph_list = child_list;
            return;
        }

        unsigned long size = graph_list.size();
        graph_list.insert( graph_list.end(), child_list.begin(), child_list.end());
        std::sort(graph_list.begin(), graph_list.end(), [](const Graph &g1, const Graph &g2) {return g1.getFitness() < g2.getFitness();});
        graph_list.erase(graph_list.begin() + size, graph_list.end());
    }
};

#endif //GRAPHCOLORING_PROBLEM_H
