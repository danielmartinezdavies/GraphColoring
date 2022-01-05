//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_NODE_H
#define GRAPHCOLORING_NODE_H

#include <random>
#include <utility>
#include <vector>
#include <string>

static const std::string empty_color = "None";
static std::random_device dev;
std::mt19937 rng(dev());

class Node{
public:
    std::vector<unsigned long> adjacentNodeList;

    std::string color = "grey";
    Node(){}
    explicit Node(std::string color, std::vector<unsigned long> adjacentNodeList): color(std::move(color)), adjacentNodeList(std::move(adjacentNodeList)){}
    std::string generateValidColor(const std::vector<Node> &NodeList, const std::vector<std::string> &color_list) const{
        std::vector<std::string> valid_color_list;
        for(auto &color : color_list){
            if(this->hasValidColor(NodeList, color)) valid_color_list.push_back(color);
        }

        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,valid_color_list.size()-1);
        auto index = dist6(rng);
        return valid_color_list[index];
    }
    bool hasValidColor(const std::vector<Node> &NodeList, const std::string &color) const{
        if(color == empty_color) return true;
        for(const auto &index :this->adjacentNodeList){
            if(NodeList[index].color == color) return false;
        }
        return true;
    }
};

#endif //GRAPHCOLORING_NODE_H
