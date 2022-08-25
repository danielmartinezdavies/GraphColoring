#ifndef GRAPHCOLORING_COLOREDGRAPH_H
#define GRAPHCOLORING_COLOREDGRAPH_H
#include "Node.h"
#include <boost/graph/graphviz.hpp>
#include "boost/graph/sequential_vertex_coloring.hpp"
#include "Graph.h"


class ColoredGraph{

public:
    std::vector<ColoredNode> colored_node_list;
    unsigned long fitness;

    ColoredGraph(int size){
        colored_node_list.resize(size);
    }

    ColoredGraph& operator=(const ColoredGraph& g)= default;
    ColoredGraph(const ColoredGraph &g): fitness(g.fitness), colored_node_list(g.colored_node_list) {}

    ~ColoredGraph(){}

    void colorGraph(std::vector<Node> &node_list, const std::vector<int> &color_list) {
        for(int i = 0; i < colored_node_list.size();i++){
            colored_node_list[i].node_color = node_list[i].generateValidColor(colored_node_list, color_list);
        }
        fitness = getNumColorsUsed();
    }
    void colorGraphEmpty() {
        for(auto &node : colored_node_list){
            node.node_color = empty_color;
        }
        fitness = 0;
    }

    void colorGraphGreedy(std::vector<Node> &node_list, const std::vector<int> &color_list) {
        for(int i = 0; i < colored_node_list.size();i++){
            for(auto &color : color_list)
                if(node_list[i].hasValidColor(colored_node_list, color)) {
                    colored_node_list[i].node_color = color;
                    break;
                }
        }
        fitness = getNumColorsUsed();
    }

    void colorGraph(std::vector<Node> &node_list, const ColoredGraph& father, const ColoredGraph& mother,const std::vector<int> &color_list){
        std::uniform_int_distribution<std::mt19937::result_type> dist2(0,1);
        for(int i = 0; i < father.colored_node_list.size();i++){
            auto &child_node = colored_node_list[i];
            auto &father_node = father.colored_node_list[i];
            auto &mother_node = mother.colored_node_list[i];
            auto rnd = dist2(rng);
            if(rnd == 0 && node_list[i].hasValidColor(colored_node_list, father_node.node_color))
                child_node.node_color = father_node.node_color;
            else if(node_list[i].hasValidColor(colored_node_list, mother_node.node_color))
                child_node.node_color = mother_node.node_color;
            else
                child_node.node_color = node_list[i].generateValidColor( colored_node_list, color_list);
        }
        fitness = getNumColorsUsed();
    }

    void crossOver(std::vector<Node> &node_list,const ColoredGraph& father, const ColoredGraph& mother, const std::vector<int> &color_list){
        colorGraph(node_list, father, mother, color_list);
    }

    void mutate(std::vector<Node> &node_list, int prob, const std::vector<int> &color_list) {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0,prob);
        for(int i = 0; i < colored_node_list.size();i++){
            if(dist(rng) == 0)
                colored_node_list[i].node_color = node_list[i].generateValidColor(colored_node_list, color_list);
        }
        fitness = getNumColorsUsed();
    }

    void exportToDot(std::vector<Node> &node_list, const std::string& filename) const {
        Graph::MyGraph graph;
        for(const auto &n : colored_node_list){
            auto vertex_id = add_vertex(graph);
            std::stringstream stream;
            stream << std::hex << n.node_color;
            graph[vertex_id].color = "#" + stream.str();
        }
        for(int i = 0; i < node_list.size();i++){
            Node n = node_list[i];
            for(int j = 0; j <  n.adjacentNodeList.size(); j++){
                if( i < n.adjacentNodeList[j])
                    boost::add_edge(i,n.adjacentNodeList[j], graph);
            }
        }

        boost::dynamic_properties dp;
        dp.property("fillcolor", get(&vertex_info::color, graph));
        dp.property("style", get(&vertex_info::style, graph));
        dp.property("node_id", get(boost::vertex_index, graph));

        std::ofstream output_file(filename);
        write_graphviz_dp(output_file, graph, dp);
        output_file.close();
    }

    unsigned long getNumColorsUsed() const{
        std::set<int> colors;
        for(const ColoredNode &n : colored_node_list){
            colors.insert(n.node_color);
        }
        return colors.size();
    }
    unsigned long getFitness() const{
        return fitness;
    }
};

#endif //GRAPHCOLORING_COLOREDGRAPH_H
