//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_PROBLEM_H
#define GRAPHCOLORING_PROBLEM_H

#include "boost/graph/sequential_vertex_coloring.hpp"
#include "ColoredGraph.h"

class Problem{

    Graph base_graph;
    std::vector<ColoredGraph> graph_list;
    std::vector<int> color_list;

    const int mutation_prob = 1000;
    const int tournament_size = 2;
    const bool replace_old_generation = true;

public:
    Problem(const std::string &input_file, int size, int mutation_prob, int tournament_size, bool replace_old_generation): base_graph(input_file), mutation_prob(mutation_prob), tournament_size(tournament_size), replace_old_generation(replace_old_generation){

        int maximum_color = base_graph.getMaximumDegree() + 1;
        std::cout << "Maximum fitness :" << maximum_color << std::endl;
        //Generate minimum number of different colors
        for(int i = 0; i < maximum_color; i++){
            int generated_color = generate_hex_color_code();
            while (std::find(color_list.begin(), color_list.end(), generated_color) != color_list.end()) {
                generated_color = generate_hex_color_code();
            }
            color_list.emplace_back(generated_color);
        }
        ColoredGraph cg1(base_graph.NodeList.size());
        cg1.colorGraph(base_graph.NodeList, color_list);
        graph_list.push_back(cg1);

        for(int i = 1; i < size; i++){
            ColoredGraph cg2(cg1);
            cg2.colorGraph(base_graph.NodeList,color_list);
            graph_list.push_back(cg2);
        }

        getGreedyFitness(cg1);
    }

    unsigned getGreedyFitness(const ColoredGraph &g1){
        ColoredGraph g3(g1);
        g3.colorGraphEmpty();
        g3.colorGraphGreedy(base_graph.NodeList,color_list);
        g3.exportToDot(base_graph.NodeList,"greedy_solution.txt");
        std::cout << "Greedy fitness: " << g3.getNumColorsUsed() << std::endl;
        return g3.getFitness();
    }

    int generate_hex_color_code(){
        int hex = 0;
        std::uniform_int_distribution<std::mt19937::result_type> dist(0,255*255*255);
        hex = dist(rng);
        return hex;
    }

    std::string generateSimulations(int num_gen, int run_num, bool disable_printing, std::string identifier){
        std::shared_ptr<ColoredGraph> best_graph = getBestGraph();
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

            std::vector<ColoredGraph> parent_list = selectParentList(tournament_size);
            std::vector<ColoredGraph> child_list = crossOverPopulation(parent_list);
            mutatePopulation(mutation_prob, color_list);
            selectNextGeneration(child_list, replace_old_generation);
            num_gens_since_improve++;
        }
        if(!disable_printing) std::cout << "Finished " << num_gen << " generations \n";
        std::cout << "Best fitness found: " << best_graph->getFitness() << std::endl;

        std::string file = identifier + "best_solution_found_" + std::to_string(run_num) + ".txt";
        best_graph->exportToDot(base_graph.NodeList,file);
        return csv;
    }

    void exportPopulationToFile(){
        for(int i = 0; i < graph_list.size(); i++){
            std::string filename = "output" + std::to_string(i);
            graph_list[i].exportToDot(base_graph.NodeList,filename);
        }
    }

    std::shared_ptr<ColoredGraph> getBestGraph(){
        auto best_graph = std::make_shared<ColoredGraph>(graph_list[0]);
        for(auto graph : graph_list){
            if(graph.getFitness() < best_graph->getFitness())
                best_graph = std::make_shared<ColoredGraph>(graph);
        }
        return best_graph;
    }
    std::vector<ColoredGraph> selectParentList(int tournament_s){
        std::vector<ColoredGraph> parent_list;
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

    std::vector<ColoredGraph> crossOverPopulation(std::vector<ColoredGraph> parent_list){
        std::vector<ColoredGraph> child_list;
        for(int i = 0; i < parent_list.size(); i++){
            std::uniform_int_distribution<std::mt19937::result_type> dist(0,parent_list.size()-1);
            ColoredGraph father = parent_list[dist(rng)];
            ColoredGraph mother = parent_list[dist(rng)];
            ColoredGraph child(father);
            child.colorGraphEmpty();
            child.crossOver(base_graph.NodeList, father, mother, color_list);
            child_list.emplace_back(child);
        }
        return child_list;
    }

    void mutatePopulation(int prob, const std::vector<int> &color_list){
        for(auto graph : graph_list){
            graph.mutate(base_graph.NodeList, prob, color_list);
        }
    }

    void selectNextGeneration(const std::vector<ColoredGraph> &child_list, bool replace_old_generation){
        if(replace_old_generation) {
            graph_list = child_list;
            return;
        }

        unsigned long size = graph_list.size();
        graph_list.insert( graph_list.end(), child_list.begin(), child_list.end());
        std::sort(graph_list.begin(), graph_list.end(), [](const ColoredGraph &g1, const ColoredGraph &g2) {return g1.getFitness() < g2.getFitness();});
        graph_list.erase(graph_list.begin() + size, graph_list.end());
    }
};

#endif //GRAPHCOLORING_PROBLEM_H
