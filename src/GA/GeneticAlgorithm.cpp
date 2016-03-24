#include "GeneticAlgorithm.h"
#include "Solution.h"
#include "RandomRange.h"
#include <vector>
#include <algorithm>
#include <fstream>

GeneticAlgorithm::GeneticAlgorithm(const double mutation_rate, const int population): mutation_rate_(mutation_rate), population_(population) {
}

void GeneticAlgorithm::print() const {
    std::cout << "=== Populations ===" << std::endl;
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < solutions_[i].size(); j += 1) {
	    std::cout << solutions_[i][j] << " ";
	}
	std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "=== Fitness ===" << std::endl;
    for (size_t i = 0; i < population_; i += 1) {
        std::cout << fitness_[i] << std::endl;
    }
}

void GeneticAlgorithm::initial(const int dimension, std::vector<double> &rangeMin, std::vector<double> &rangeMax, const double (*func)(const std::vector<double> &)) {
    fitnessFunc_ = func;
    still_ = converge_;
    best_fitness_ = INT32_MIN;
    last_best_fitness_ = INT32_MIN;

    solutions_ = std::vector<Solution>(population_, Solution());
    fitness_ = std::vector<double>(population_, 0);
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < dimension; j += 1) {
	    solutions_[i].push_back(RandomRange::random<double>(rangeMin[j], rangeMax[j]));
	}
        fitness_[i] = fitnessFunction_(solutions_[i]);
    }
}

void GeneticAlgorithm::selection() {
    selected_.clear();
    const size_t tournament_size_ = 2;
    for (size_t i = 0; i < solutions_.size(); i += tournament_size_) {
        fitness_[i] < fitness_[i+1] ? selected_.push_back((int)i) : selected_.push_back((int)i+1);
    }
    if (selected_.size() % 2) selected_.pop_back();
}


void GeneticAlgorithm::crossover() {
    std::random_shuffle(selected_.begin(), selected_.end());
    for (int i = 0; i < selected_.size(); i += 2) {
        // TODO
	// fitnessFunction_(first_child) < fitnessFunction_(solutions_[selected_[i]]) ? solutions_[selected_[i]] = first_child : solutions_[selected_[i]];
        // fitnessFunction_(second_child) < fitnessFunction_(solutions_[selected_[i+1]]) ? solutions_[selected_[i+1]] = second_child : solutions_[selected_[i+1]];
    }
}

void GeneticAlgorithm::mutation() {
    for (size_t i = 0; i < population_; i += 1) {
        if ( solutions_[i].size() > 2 && RandomRange::random<double>(0, 1) < mutation_rate_) {
            const int mutation_point = RandomRange::random<int>(0, (int)solutions_[i].size() - 3);
            // TODO
	}
    }
}

void GeneticAlgorithm::evaluate_() {
    for (size_t i = 0; i < solutions_.size(); i += 1) {
        const int fitness__ = fitnessFunction_(solutions_[i]);
        if (best_fitness_ > fitness__) {
            best_fitness_ = fitness__ ;
            best_solution_ = Solution(solutions_[i]);
        }
        fitness_[i] = fitness__;
    }
}

const double GeneticAlgorithm::fitnessFunction_(const Solution &solution) const {
    return fitnessFunc_(solution);
}

const bool GeneticAlgorithm::notConverge() {
    evaluate_();
    if (best_fitness_ == last_best_fitness_) {
        if (still_ == 0 ) return false;
        else still_--;
        return true;
    }
    else {
        still_ = converge_;
        last_best_fitness_ = best_fitness_;
        return true;
    }
}
