#include <iostream>
#include <vector>
#include "GeneticAlgorithm.h"

const double myfunc(const std::vector<double> &param) {
    return param[0] + param[1];
}

int main(int argc, const char * argv[]) {
    GeneticAlgorithm geneticAlgorithm(0.6, 20);
    std::vector<double> rangeMin {0, 100}, rangeMax {10, 110};
    geneticAlgorithm.initial(2, rangeMin, rangeMax, myfunc);
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
