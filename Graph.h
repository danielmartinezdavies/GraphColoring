//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_GRAPH_H
#define GRAPHCOLORING_GRAPH_H
#include "Node.h"
#include <boost/graph/graphviz.hpp>

struct vertex_info {
    std::string color = "grey";
    std::string style = "filled";
};


class Graph{
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vertex_info, boost::no_property > MyGraph;
public:
    std::vector<Node> NodeList;

    Graph(std::string input_name){
        std::ifstream input_file(input_name);

        MyGraph graph;
        boost::dynamic_properties dp;
        dp.property("node_id", get(boost::vertex_index, graph));

        read_graphviz(input_file, graph, dp);
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

    }
    bool hasValidColor(const Node &node){
        for(const auto &index :node.adjacentNodeList){
            if(this->NodeList[index].color == node.color) return false;
        }
        return true;
    }

    int getNumColorsUsed(){
        std::set<std::string> colors;
        for(Node n : NodeList){
            colors.insert(n.color);
        }
        return colors.size();
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
};
#endif //GRAPHCOLORING_GRAPH_H
