#include <iostream>
#include "GeneticAlgorithm.h"

int main(int argc, const char * argv[]) {
    GeneticAlgorithm geneticAlgorithm(0.15);
    geneticAlgorithm.initial();
    do {
        geneticAlgorithm.selection();
        geneticAlgorithm.crossover();
        geneticAlgorithm.mutation();
    } while (geneticAlgorithm.notConverge());
    geneticAlgorithm.printSolution();
    //std::cout << geneticAlgorithm.getSolution() << std::endl;
    return 0;
}
