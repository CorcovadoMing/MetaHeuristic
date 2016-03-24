#include <iostream>
#include <vector>
#include "GeneticAlgorithm.h"

const double myfunc(const std::vector<double> &param) {
    return param[0] + param[1];
}

int main(int argc, const char * argv[]) {

    /*
    std::vector<double> param;
    param.push_back(1);
    param.push_back(2);
    std::cout << myfunc(param) << std::endl;
    */

    GeneticAlgorithm geneticAlgorithm(0.5, 20);
    std::vector<double> rangeMin, rangeMax;
    rangeMin.push_back(0);
    rangeMin.push_back(100);
    rangeMax.push_back(10);
    rangeMax.push_back(110);
    geneticAlgorithm.initial(2, rangeMin, rangeMax, myfunc);
    do {
        geneticAlgorithm.selection();
        geneticAlgorithm.crossover();
        geneticAlgorithm.mutation();
    } while (geneticAlgorithm.notConverge());
    geneticAlgorithm.print();
    return 0;
}
