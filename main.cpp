#include "Problem.h"

int main() {
    Problem p("../examples/input_file3.txt", 500);
    p.generateSimulations(500);
    return 0;
}