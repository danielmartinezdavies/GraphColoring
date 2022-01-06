# GraphColoring

Boost is required for compilation. To install:
       
    sudo apt-get install libboost-all-dev

The project can be compiled with:

    mkdir build
    cd build
    cmake  -DCMAKE_BUILD_TYPE=Release ..
    make

An online interpreter can be used:

    https://dreampuf.github.io/GraphvizOnline/

Alternatively, graphviz can be used:
    
    sudo apt install graphviz
    dot -Tpng best_solution_found.txt -o filename.png

     
