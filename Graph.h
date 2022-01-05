//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_GRAPH_H
#define GRAPHCOLORING_GRAPH_H
#include "Node.h"
#include <boost/graph/graphviz.hpp>
#include <random>

struct vertex_info {
    int id;
    std::string color = "grey";
    std::string style = "filled";
};

std::random_device dev;
std::mt19937 rng(dev());


class Graph{
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vertex_info, boost::no_property > MyGraph;
public:
    std::vector<Node> NodeList;

    Graph(const std::string &input_name){
        std::ifstream input_file(input_name);

        MyGraph graph;
        boost::dynamic_properties dp;
        dp.property("node_id", get(&vertex_info::id, graph));

        read_graphviz(input_file, graph, dp, "node_id");

        input_file.close();

        auto vertices = graph.m_vertices;
        for(auto &vertex : vertices){
            NodeList.emplace_back();
        }
        auto edges = graph.m_edges;
        for(auto &edge : edges){
            NodeList[edge.m_source].adjacentNodeList.push_back(edge.m_target);
            NodeList[edge.m_target].adjacentNodeList.push_back(edge.m_source);
        }
        colorGraph({"green", "yellow", "blue"});
    }

    Graph(const Graph &g1) {
        this->NodeList = g1.NodeList;
        colorGraph({"green", "yellow", "red"});
    }

    void colorGraph(const std::vector<std::string> &color_list){
        for(auto &node : NodeList){
            std::vector<std::string> valid_color_list;
            for(auto &color : color_list){
                if(hasValidColor(node, color)) valid_color_list.push_back(color);
            }

            std::uniform_int_distribution<std::mt19937::result_type> dist6(0,valid_color_list.size()-1); // distribution in range [1, 6]
            node.color = valid_color_list[dist6(rng)];
        }
    }

    void exportToDot(const std::string& filename){
        MyGraph graph;
        for(const auto &n : NodeList){
            auto vertex_id = add_vertex(graph);
            graph[vertex_id].color = n.color;
        }
        for(int i = 0; i < NodeList.size();i++){
            Node n = NodeList[i];
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
    bool hasValidColor(const Node &node){
        for(const auto &index :node.adjacentNodeList){
            if(this->NodeList[index].color == node.color) return false;
        }
        return true;
    }
    bool hasValidColor(const Node &node, const std::string &color){
        for(const auto &index :node.adjacentNodeList){
            if(this->NodeList[index].color == color) return false;
        }
        return true;
    }

    unsigned long getNumColorsUsed(){
        std::set<std::string> colors;
        for(Node n : NodeList){
            colors.insert(n.color);
        }
        return colors.size();
    }
};
#endif //GRAPHCOLORING_GRAPH_H
