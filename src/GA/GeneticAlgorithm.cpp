#include "GeneticAlgorithm.h"
#include "Solution.h"
#include "RandomRange.h"
#include <vector>
#include <algorithm>
#include <fstream>

GeneticAlgorithm::GeneticAlgorithm(const double mutation_rate): mutation_rate_(mutation_rate) {
}

void GeneticAlgorithm::printSolution() const {
    //best_solution_.print();
    std::cout << best_fitness_ << std::endl;
}

const std::string GeneticAlgorithm::getSolution() const {
    return best_solution_.printString();

}

void GeneticAlgorithm::initial() {
    still_ = converge_;
    best_fitness_ = INT32_MIN;
    last_best_fitness_ = INT32_MIN;

    solutions_ = std::vector<Solution>(population_, Solution());
    fitness_ = std::vector<int>(solutions_.size(), 0);
    for (size_t i = 0; i < solutions_.size(); i += 1) {
        std::vector<int> path;
        solutions_[i].insteadAll(path);
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

const int GeneticAlgorithm::fitnessFunction_(const Solution &solution) const {
    // TODO
    return 0;
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
