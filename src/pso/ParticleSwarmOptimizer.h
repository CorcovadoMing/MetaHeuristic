#ifndef __ParticleSwarmOptimizer__
#define __ParticleSwarmOptimizer__

#include <vector>
#include <iostream>
#include "RandomRange.h"
#include "Solution.h"

namespace Distribution {
    extern const int Uniform;
    extern const int Normal;
}

class Parameters {
public:
    int Populations = 20;
    double MutationRate = 0.6;
    int Dimensions = 0;
    int DimensionsInt = 0;
    std::vector<double> RangeMin, RangeMax;
    const double (*FitnessFunction) (const std::vector<double> &);
    int MutationType = 0;
    double MutationNormalStd = 0.2;
};

class GeneticAlgorithm {
public:
    GeneticAlgorithm() {}
    const std::vector<double> getResult() const;
    const double getFitness() const;
    void print() const;
    void initial(const Parameters &);
    void selection();
    void crossover();
    void mutation();
    const bool notConverge();

private:
    void evaluate_();
    const double fitnessFunction_(const Solution &) const;
    const double (*fitnessFunc_) (const std::vector<double> &);
    int mutation_type_;
    double mutation_std_;
    int population_;
    int int_index_;
    double best_fitness_ = INT32_MIN;
    double last_best_fitness_ = INT32_MIN;
    const int converge_ = 3;
    int still_ = converge_;
    Solution best_solution_;
    double mutation_rate_;
    std::vector<Solution> solutions_;
    std::vector<double> fitness_;
    std::vector<int> selected_;
    std::vector<double> rangeMin_, rangeMax_;
};

#endif
