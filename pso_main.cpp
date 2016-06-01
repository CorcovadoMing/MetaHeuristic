#include <iostream>
#include <vector>
#include "src/ga/GeneticAlgorithm.h"

const double myfunc(const std::vector<double> &param) {
    return param[0]*100 + param[1] + param[2] + param[3];
}

int main(int argc, const char * argv[]) {
    // Declare GA class with mutation rate 0.6 and population size 20
    GeneticAlgorithm geneticAlgorithm;
    
    // Each parameters rangeMin and rangeMax
    std::vector<double> rangeMin {0, 0, 0, 100}, rangeMax {5, 10, 10, 110};
    
    // Parameters
    Parameters param;
    param.MutationType = Distribution::Normal; // (Distribution::Normal, Distribution::Uniform)
    param.MutationNormalStd = 0.1;
    param.RangeMax = rangeMax;
    param.RangeMin = rangeMin;
    param.Dimensions = 4;
    param.DimensionsInt = 2;
    param.FitnessFunction = myfunc;
    param.Populations = 20;
    param.MutationRate = 0.6;
    
    geneticAlgorithm.initial(param);
    
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
