//
// Created by danny on 5/1/22.
//

#ifndef GRAPHCOLORING_PARAMETERS_H
#define GRAPHCOLORING_PARAMETERS_H

#include <random>
#include <iostream>

std::mt19937 rng(1);

class Parameters{
public:
    std::string input_file = "../examples/input_file.txt";
    int  population_size = 2000;
    int  mutation_prob = 2000;
    int  tournament_size = 3;
    bool replace_old_generation = true;
    int  generations_since_improvement = 100;
    int  num_runs = 1;
    bool disable_printing = false;
    std::string identifier = "";

    Parameters() = default;

    Parameters(const std::string &inputFile, const int populationSize, const int mutationProb, const int tournamentSize,
               const bool replaceOldGeneration, const int generationsSinceImprovement, const int numRuns) : input_file(
            inputFile), population_size(populationSize), mutation_prob(mutationProb), tournament_size(tournamentSize),
                                                                                                            replace_old_generation(
                                                                                                                    replaceOldGeneration),
                                                                                                            generations_since_improvement(
                                                                                                                    generationsSinceImprovement),
                                                                                                            num_runs(
                                                                                                                    numRuns) {}
};

Parameters parseInputParameters(const std::vector<std::string> &parameters){
    Parameters p;
    auto isSmaller = [&](int i) {return i < parameters.size()-1;};
    for(int i = 0; i < parameters.size();i++) {
        if (parameters[i] == "--help") {
            std::cout << "Possible Parameters:\n"
                         "--input_file\n"
                         "--population_size\n"
                         "--mutation_prob\n"
                         "--tournament_size\n"
                         "--num_runs\n"
                         "--seed\n"
                         "--disable_printing\n"
                         "--identifier\n"
                         << std::endl;
            exit(0);

        }
        else if (isSmaller(i) && parameters[i] == "--input_file") {
            p.input_file = parameters[i+1];
        }
        else if (isSmaller(i) && parameters[i] == "--population_size") {
            p.population_size = std::stoi(parameters[i+1]);
        }
        else if (isSmaller(i) && parameters[i] == "--mutation_prob") {
            p.mutation_prob = std::stoi(parameters[i+1]);
        }
        else if (isSmaller(i) && parameters[i] == "--tournament_size") {
            p.tournament_size = std::stoi(parameters[i+1]);
        }
        else if (isSmaller(i) && parameters[i] == "--num_runs") {
            p.num_runs = std::stoi(parameters[i+1]);
        }
        else if (isSmaller(i) && parameters[i] == "--seed") {
            rng.seed(std::stoi(parameters[i+1]));
        }
        else if (parameters[i] == "--disable_printing") {
            p.disable_printing = true;
        }
        else if (isSmaller(i) && parameters[i] == "--identifier") {
            p.identifier = parameters[i+1];
        }
    }

    return p;
}



#endif //GRAPHCOLORING_PARAMETERS_H

