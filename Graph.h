//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_GRAPH_H
#include "Node.h"
#include <boost/graph/graphviz.hpp>


struct vertex_info {
    int id;
    std::string color = "none";
    std::string style = "filled";
};


class Graph{
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vertex_info, boost::no_property > MyGraph;
public:
    std::vector<Node> NodeList;
    const std::vector<std::string> color_list;
    unsigned long fitness;

    Graph(const std::string &input_name, const std::vector<std::string> &color_list): color_list(color_list){
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
        colorGraph(color_list);
    }

    Graph& operator=(const Graph& g){
        this->NodeList = g.NodeList;
        this->fitness = g.fitness;
        return *this;
    }
    Graph(const Graph &g): color_list(g.color_list), NodeList(g.NodeList){
        colorGraph(color_list);
    }
    Graph(const Graph &g, std::string color): color_list(g.color_list), NodeList(g.NodeList){
        colorGraph({color});
    }
    ~Graph(){}

    void colorGraph(const std::vector<std::string> &color_list) {
        for(auto &node : NodeList){
            node.color = node.generateValidColor(NodeList, color_list);
        }
        fitness = getNumColorsUsed();
    }

    void colorGraph(const Graph& father, const Graph& mother){
        std::uniform_int_distribution<std::mt19937::result_type> dist2(0,1);
        for(int i = 0; i < father.NodeList.size();i++){
            auto &child_node = NodeList[i];
            auto &father_node = father.NodeList[i];
            auto &mother_node = mother.NodeList[i];
            auto rnd = dist2(rng);
            if(rnd == 0 && child_node.hasValidColor(NodeList, father_node.color))
                child_node.color = father_node.color;
            else if(child_node.hasValidColor(NodeList, mother_node.color))
                child_node.color = mother_node.color;
            else
                child_node.generateValidColor(NodeList, color_list);
        }
        fitness = getNumColorsUsed();
    }

    void crossOver(const Graph& father, const Graph& mother){
        colorGraph(father, mother);
    }

    void mutate(int prob){
        std::uniform_int_distribution<std::mt19937::result_type> dist(0,prob);
        for(auto &node : NodeList){
            if(dist(rng) == 0)
                node.color = node.generateValidColor(NodeList, color_list);
        }
    }

    void exportToDot(const std::string& filename) const {
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

    unsigned long getNumColorsUsed(){
        std::set<std::string> colors;
        for(const Node &n : NodeList){
            colors.insert(n.color);
        }
        return colors.size();
    }
    unsigned long getFitness() const{
        return fitness;
    }
};
#endif //GRAPHCOLORING_GRAPH_H
