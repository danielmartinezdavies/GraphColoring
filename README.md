# GraphColoring
This project offers a solution to the Graph Coloring problem using 
a Genetic Algorithm. Graph Coloring tries to find the least amount of 
colors needed such that two adjacent nodes do not share the same color.
Graphs are read and written in the dot language. 

For example:

![picture of a graph without any coloring](./resources/graph.png)
![picture of a graph without any coloring](./resources/graph_colored.png)

![picture of a larger second graph without any coloring](./resources/graph2.png) 
![picture of a larger second graph without any coloring](./resources/graph2_colored.png)

## Building
This project was developed for Linux.
The project can be compiled with the following:

    mkdir build
    cd build
    cmake  -DCMAKE_BUILD_TYPE=Release ..
    make

Boost is required for processing and generating graphs. To install using the apt package manager:
    
    sudo apt-get install libboost-all-dev

The generated output files in the dot language can be viewed by using an interpreter.

An online interpreter can be used:

    https://dreampuf.github.io/GraphvizOnline/

Alternatively, graphviz can be used to generate the image file:
    
    sudo apt install graphviz
    dot -Tpng best_solution_found.txt -o filename.png

## Testing

There is a suite of tests included in the project. These can be run using the following command:
    
    ctest -j

     
