#include <iostream>
#include <vector>
#include "src/pso/ParticleSwarmOptimizer.h"

const double myfunc(const std::vector<double> &param) {
    return param[0]*100 + param[1] + param[2] + param[3];
}

int main(int argc, const char * argv[]) {
    ParticleSwarmOptimizer pso;
    
    // Each parameters rangeMin and rangeMax
    std::vector<double> rangeMin {0, 0, 0, 100}, rangeMax {5, 10, 10, 110};
    
    // Parameters
    Parameters param;
    param.RangeMax = rangeMax;
    param.RangeMin = rangeMin;
    param.FitnessFunction = myfunc;
    param.Dimensions = 4;
    param.DimensionsInt = 2;
    
    pso.initial(param);
    pso.print();
/*    
    // Result is fit into a vector
    std::vector<double> result = pso.getResult();
    for (const auto i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "Fitness: " << pso.getFitness() << std::endl;
*/
    return 0;
}
