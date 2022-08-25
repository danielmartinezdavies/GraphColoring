#ifndef GRAPHCOLORING_COLOREDNODE_H
#define GRAPHCOLORING_COLOREDNODE_H

#include "Parameters.h"

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <random>

static const std::string empty_color = "None";


class ColoredNode{
public:
    std::string node_color = "grey";
    ColoredNode()= default;
    explicit ColoredNode(std::string color): node_color(std::move(color)) {}
};


#endif //GRAPHCOLORING_COLOREDNODE_H
