#include "GeneticAlgorithm.h"
#include "Solution.h"
#include <vector>
#include <algorithm>
#include <fstream>

namespace Distribution {
    const int Uniform = 0;
    const int Normal = 1;
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
    std::cout << std::endl;
    std::cout << "=== Best Solution ===" << std::endl;
    for (size_t i = 0; i < best_solution_.size(); i += 1) {
        std::cout << best_solution_[i] << " ";
    }
    std::cout << "Fitness: " << best_fitness_ << std::endl;
}

const std::vector<double> GeneticAlgorithm::getResult() const {
    return best_solution_;
}

const double GeneticAlgorithm::getFitness() const {
    return best_fitness_;
}

void GeneticAlgorithm::initial(const Parameters &Param) {
    rangeMax_ = Param.RangeMax;
    rangeMin_ = Param.RangeMin;
    fitnessFunc_ = Param.FitnessFunction;
    still_ = converge_;
    best_fitness_ = INT32_MIN;
    last_best_fitness_ = INT32_MIN;
    mutation_type_ = Param.MutationType;
    mutation_std_ = Param.MutationNormalStd;
    mutation_rate_ = Param.MutationRate;
    int_index_ = Param.DimensionsInt;
    population_ = Param.Populations;

    const int dimension = Param.Dimensions;

    solutions_ = std::vector<Solution>(population_, Solution());
    fitness_ = std::vector<double>(population_, 0);
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < dimension; j += 1) {
            if (j < int_index_)
                solutions_[i].push_back(RandomRange::random<int>(rangeMin_[j], rangeMax_[j]));
            else
                solutions_[i].push_back(RandomRange::random<double>(rangeMin_[j], rangeMax_[j]));
	    }
            fitness_[i] = fitnessFunction_(solutions_[i]);
    }
}

void GeneticAlgorithm::selection() {
    selected_.clear();
    // TODO: Need a better method, the current limitation is the size of population needs to be multiplied by four
    const size_t tournament_size_ = 2;
    for (size_t i = 0; i < solutions_.size(); i += tournament_size_) {
        fitness_[i] < fitness_[i+1] ? selected_.push_back((int)i) : selected_.push_back((int)i+1);
    }
    if (selected_.size() % 2) selected_.pop_back();
}


void GeneticAlgorithm::crossover() {
    std::random_shuffle(selected_.begin(), selected_.end());
    for (int i = 0; i < selected_.size(); i += 2) {
        int cutPoint = RandomRange::random<int>(1, solutions_[0].size()-1); // excluded both-end [X][O]
        Solution firstChild = solutions_[selected_[i]];
	Solution secondChild = solutions_[selected_[i+1]];

	for (int j = cutPoint; j < solutions_[0].size(); j += 1) {
	    firstChild[j] = solutions_[selected_[i+1]][j];
	    secondChild[j] = solutions_[selected_[i]][j];
	}
	
	fitnessFunction_(firstChild) < fitnessFunction_(solutions_[selected_[i]]) ? solutions_[selected_[i]] = firstChild : solutions_[selected_[i]];
        fitnessFunction_(secondChild) < fitnessFunction_(solutions_[selected_[i+1]]) ? solutions_[selected_[i+1]] = secondChild : solutions_[selected_[i+1]];
    }
}

void GeneticAlgorithm::mutation() {
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < solutions_[i].size(); j += 1) {
	    if (RandomRange::random<double>(0, 1) < mutation_rate_) {
            if (j < int_index_) {
	            if (mutation_type_ == 0) solutions_[i][j] = RandomRange::random<int>(rangeMin_[j], rangeMax_[j]);
                else solutions_[i][j] = std::min(std::max(RandomRange::normal<int>(solutions_[i][j], mutation_std_), (int)rangeMin_[j]), (int)rangeMax_[j]);
            }
            else {
                if (mutation_type_ == 0) solutions_[i][j] = RandomRange::random<double>(rangeMin_[j], rangeMax_[j]);
                else solutions_[i][j] = std::min(std::max(RandomRange::normal<double>(solutions_[i][j], mutation_std_), rangeMin_[j]), rangeMax_[j]);
            }
        }
	}
    }
}

void GeneticAlgorithm::evaluate_() {
    for (size_t i = 0; i < solutions_.size(); i += 1) {
        const double fitness__ = fitnessFunction_(solutions_[i]);
        if (best_fitness_ < fitness__) {
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
        else still_ -= 1;
        return true;
    }
    else {
        still_ = converge_;
        last_best_fitness_ = best_fitness_;
        return true;
    }
}
