#ifndef __GeneticAlgorithm__
#define __GeneticAlgorithm__

#include <vector>
#include <iostream>
#include "Solution.h"

namespace Distribution {
    extern const int Uniform;
    extern const int Normal;
}

class MutationType {
public:
    int type = 0;
    double std = 0.2;
};

class GeneticAlgorithm {
public:
    GeneticAlgorithm(const double, const int);
    const std::vector<double> getResult() const;
    const double getFitness() const;
    void print() const;
    void initial(const int, const int, std::vector<double> &, std::vector<double> &, const double (*func)(const std::vector<double> &), const MutationType &);
    void selection();
    void crossover();
    void mutation();
    const bool notConverge();

private:
    void evaluate_();
    const double fitnessFunction_(const Solution &) const;
    const double (*fitnessFunc_)(const std::vector<double> &);
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
