//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_NODE_H
#define GRAPHCOLORING_NODE_H
class Node{
public:
    std::vector<unsigned long> adjacentNodeList;

    std::string color = "grey";
    Node(){}
    explicit Node(const std::string &color, std::vector<unsigned long> adjacentNodeList): color(color), adjacentNodeList(adjacentNodeList){}

};

#endif //GRAPHCOLORING_NODE_H
