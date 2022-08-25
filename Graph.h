//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_GRAPH_H
#include "Node.h"
#include <boost/graph/graphviz.hpp>
#include "boost/graph/sequential_vertex_coloring.hpp"

struct vertex_info {
    int id;
    std::string color = "none";
    std::string style = "filled";
};


class Graph{

public:
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vertex_info, int, boost::property<boost::vertex_color_t, boost::default_color_type>> MyGraph;
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::property<boost::vertex_index_t, int, boost::property<boost::vertex_color_t, boost::default_color_type>>>  GraphType;

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
    }


    int getMaximumDegree() const {
        int maximum = 0;
        for(auto & node : NodeList) {
            if(maximum < node.adjacentNodeList.size()){
                maximum = node.adjacentNodeList.size();
            }
        }
        return maximum;
    }
};
#endif //GRAPHCOLORING_GRAPH_H
