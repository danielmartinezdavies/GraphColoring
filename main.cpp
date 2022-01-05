#include "Problem.h"

int main() {
    Problem p("../examples/input_file3.txt", 200);
    p.generateSimulations(10000);
    return 0;
}