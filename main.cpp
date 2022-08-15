#include "Problem.h"
#include "Parameters.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> allArgs(argv, argv + argc);

    std::string csv = "";
    const Parameters param = parseInputParameters(allArgs);

    for(int i = 0; i < param.num_runs;i++){
        std::cout << "\n---\n---\n" << "Run " << i << "\n---\n---\n" <<  std::endl;
        Problem p(param.input_file, param.population_size, param.mutation_prob, param.tournament_size, param.replace_old_generation);
        csv += p.generateSimulations(param.generations_since_improvement, i);
    }
    std::string name = "output" + std::to_string(param.population_size) + "_" + std::to_string(param.mutation_prob)
            + "_" + std::to_string(param.tournament_size) +"_" +  std::to_string(param.replace_old_generation) + ".csv";
    std::ofstream output_file(name);
    output_file << csv;
    output_file.close();
    return 0;
}