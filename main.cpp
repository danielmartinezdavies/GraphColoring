#include "Problem.h"
#include "Parameters.h"

int main() {
    Problem p(input_file, population_size, mutation_prob, tournament_size, replace_old_generation);
    p.generateSimulations(generations_since_improvement);
    return 0;
}