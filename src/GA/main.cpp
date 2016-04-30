#include <iostream>
#include <vector>
#include "GeneticAlgorithm.h"

const double myfunc(const std::vector<double> &param) {
    return param[0] + param[1];
}

int main(int argc, const char * argv[]) {
    GeneticAlgorithm geneticAlgorithm(0.6, 20);
    std::vector<double> rangeMin {0, 100}, rangeMax {10, 110};
    MutationType mutation_type;
    mutation_type.type = Distribution::Normal;
    mutation_type.std = 0.2;
    geneticAlgorithm.initial(2, rangeMin, rangeMax, myfunc, mutation_type);
    do {
        geneticAlgorithm.selection();
        geneticAlgorithm.crossover();
        geneticAlgorithm.mutation();
    } while (geneticAlgorithm.notConverge());
    //geneticAlgorithm.print(); // for Debugging

    std::vector<double> result = geneticAlgorithm.getResult();
    for (const auto i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "Fitness: " << geneticAlgorithm.getFitness() << std::endl;

    return 0;
}
