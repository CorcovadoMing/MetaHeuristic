#include <iostream>
#include <vector>
#include "GeneticAlgorithm.h"

int main(int argc, const char * argv[]) {
    GeneticAlgorithm geneticAlgorithm(0.15, 20);

    std::vector<double> rangeMin, rangeMax;
    rangeMin.push_back(0);
    rangeMin.push_back(0);
    rangeMax.push_back(10);
    rangeMax.push_back(10);

    geneticAlgorithm.initial(2, rangeMin, rangeMax);
    //do {
    //    geneticAlgorithm.selection();
    //    geneticAlgorithm.crossover();
    //    geneticAlgorithm.mutation();
    //} while (geneticAlgorithm.notConverge());
    //geneticAlgorithm.printSolution();
    geneticAlgorithm.printAll();
    //std::cout << geneticAlgorithm.getSolution() << std::endl;
    return 0;
}
