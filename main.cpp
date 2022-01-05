#include "Problem.h"

int main() {
    Problem p("../examples/input_file.txt", 50);
    p.generateSimulations(100);
    return 0;
}