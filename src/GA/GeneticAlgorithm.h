#ifndef __GeneticAlgorithm__
#define __GeneticAlgorithm__

#include <vector>
#include <iostream>
#include "Solution.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(const double, const int);

    void goal(const int, const int);
    void printSolution() const;
    void printAll() const;
    const std::string getSolution() const;

    void initial(const int, std::vector<double> &, std::vector<double> &, const double (*func)(const std::vector<double> &));
    void selection();
    void crossover();
    void mutation();
    const bool notConverge();

private:
    void evaluate_();
    const int fitnessFunction_(const Solution &) const;
    const double (*fitnessFunc_)(const std::vector<double> &);
    int population_;
    int best_fitness_ = INT32_MIN;
    int last_best_fitness_ = INT32_MIN;
    const int converge_ = 3;
    int still_ = converge_;
    Solution best_solution_;
    double mutation_rate_;
    std::vector<Solution> solutions_;
    std::vector<int> fitness_, selected_;
};

#endif
