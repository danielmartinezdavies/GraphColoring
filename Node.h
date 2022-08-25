//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_NODE_H
#define GRAPHCOLORING_NODE_H

#include "Parameters.h"
#include "ColoredNode.h"


#include <utility>
#include <vector>
#include <string>
#include <iostream>


class Node{
public:
    std::vector<unsigned long> adjacentNodeList;
    Node(){}
    explicit Node(std::vector<unsigned long> adjacentNodeList):  adjacentNodeList(std::move(adjacentNodeList)){}

    std::string generateValidColor(const std::vector<ColoredNode> &colored_node_list, const std::vector<std::string> &color_list) const{
        std::vector<std::string> valid_color_list;
        for(auto &color : color_list){
            if(this->hasValidColor(colored_node_list, color)) valid_color_list.push_back(color);
        }

        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,valid_color_list.size()-1);
        auto index = dist6(rng);
        return valid_color_list[index];
    }
    bool hasValidColor(const std::vector<ColoredNode> &colored_node_list, const std::string &color) const{
        for(const auto &index :this->adjacentNodeList){
            if(colored_node_list[index].node_color == color) return false;
        }
        return true;
    }
};

#endif //GRAPHCOLORING_NODE_H
