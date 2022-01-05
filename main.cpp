#include "Problem.h"

int main() {
    Problem p("../examples/input_file2.txt", 100);
    p.generateSimulations(1000);
    return 0;
}