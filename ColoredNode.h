#ifndef GRAPHCOLORING_COLOREDNODE_H
#define GRAPHCOLORING_COLOREDNODE_H

#include "Parameters.h"

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <random>

static const int empty_color = -1;


class ColoredNode{
public:
    int node_color = 0;
    ColoredNode()= default;
    explicit ColoredNode(int color): node_color(color) {}
};


#endif //GRAPHCOLORING_COLOREDNODE_H
