#include <iostream>
#include <vector>
#include "GeneticAlgorithm.h"

const double myfunc(const std::vector<double> &param) {
    return param[0]*100 + param[1] + param[2] + param[3];
}

int main(int argc, const char * argv[]) {
    // Declare GA class with mutation rate 0.6 and population size 20
    GeneticAlgorithm geneticAlgorithm(0.6, 20);
    
    // Each parameters rangeMin and rangeMax
    std::vector<double> rangeMin {0, 0, 0, 100}, rangeMax {5, 10, 10, 110};
    
    // Declare the mutation type
    MutationType mutation_type;
    // Choose one of (Distribution::Uniform, Distribution::Normal)
    mutation_type.type = Distribution::Normal;
    // Only affect to Distribution::Normal
    mutation_type.std = 0.1;
    
    // Initial <total dimenstions>, <# integers>, <rangeMin>, <rangeMax>, <custom fitness function>, <mutation type>
    geneticAlgorithm.initial(4, 2, rangeMin, rangeMax, myfunc, mutation_type);
    
    // No need to modify this while loop
    do {
        geneticAlgorithm.selection();
        geneticAlgorithm.crossover();
        geneticAlgorithm.mutation();
    } while (geneticAlgorithm.notConverge());
    //geneticAlgorithm.print(); // for Debugging

    // Result is fit into a vector
    std::vector<double> result = geneticAlgorithm.getResult();
    for (const auto i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "Fitness: " << geneticAlgorithm.getFitness() << std::endl;

    return 0;
}
