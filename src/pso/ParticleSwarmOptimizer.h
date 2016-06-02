#ifndef __ParticleSwarmOptimizer__
#define __ParticleSwarmOptimizer__

#include <vector>
#include <iostream>
#include "RandomRange.h"
#include "Solution.h"

class Parameters {
public:
    int Populations = 20;
    int Dimensions = 0;
    int DimensionsInt = 0;
    std::vector<double> RangeMin, RangeMax;
    const double (*FitnessFunction) (const std::vector<double> &);
    double w = 0.6;
    double c1 = 0.7;
    double c2 = 0.7;
};

class ParticleSwarmOptimizer {
public:
    ParticleSwarmOptimizer() {}
    const std::vector<double> getResult() const;
    const double getFitness() const;
    void print() const;
    void initial(const Parameters &);

private:
    void evaluate_();
    const double fitnessFunction_(const Solution &) const;
    const double (*fitnessFunc_) (const std::vector<double> &);
    int population_;
    int int_index_;
    double best_fitness_ = INT32_MIN;
    Solution best_solution_;
    std::vector<Solution> positions_, pbest_positions_;
    std::vector<double> fitness_, velocity_, gbest_position_;
    std::vector<double> rangeMin_, rangeMax_;
    double w_, c1_, c2_;
};

#endif
