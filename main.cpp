#include "Problem.h"
#include "Parameters.h"

int main(int argc, char *argv[]) {

    if(argc > 2) return -1;
    if(argc == 2) input_file = argv[1];
    std::string csv = "";
    for(int i = 0; i < num_runs;i++){
        std::cout << "\n---\n---\n" << "Run " << i << "\n---\n---\n" <<  std::endl;
        Problem p(input_file, population_size, mutation_prob, tournament_size, replace_old_generation);
        csv += p.generateSimulations(generations_since_improvement, i);
    }
    std::string name = "output" + std::to_string(population_size) + "_" + std::to_string(mutation_prob)
            + "_" + std::to_string(tournament_size) +"_" +  std::to_string(replace_old_generation) + ".csv";
    std::ofstream output_file(name);
    output_file << csv;
    output_file.close();
    return 0;
}