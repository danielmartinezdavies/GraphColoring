#include "Problem.h"

int main() {
    Problem p("../examples/input_file.txt", 5);
    p.generateSimulations(1);
    return 0;
}