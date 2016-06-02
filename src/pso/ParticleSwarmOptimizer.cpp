#include "ParticleSwarmOptimizer.h"
#include "Solution.h"
#include <vector>
#include <algorithm>
#include <fstream>

void ParticleSwarmOptimizer::print() const {
    std::cout << "=== Positions ===" << std::endl;
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < positions_[i].size(); j += 1) {
	    std::cout << positions_[i][j] << " ";
	}
	std::cout << "\tVelocity: " << velocity_[i] << std::endl;
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

const std::vector<double> ParticleSwarmOptimizer::getResult() const {
    return best_solution_;
}

const double ParticleSwarmOptimizer::getFitness() const {
    return best_fitness_;
}

void ParticleSwarmOptimizer::initial(const Parameters &Param) {
    rangeMax_ = Param.RangeMax;
    rangeMin_ = Param.RangeMin;
    fitnessFunc_ = Param.FitnessFunction;
    best_fitness_ = INT32_MIN;
    int_index_ = Param.DimensionsInt;
    population_ = Param.Populations;

    const int dimension = Param.Dimensions;

    positions_ = std::vector<Solution>(population_, Solution());
    fitness_ = std::vector<double>(population_, 0);
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < dimension; j += 1) {
            if (j < int_index_)
                positions_[i].push_back(RandomRange::random<int>(rangeMin_[j], rangeMax_[j]));
            else
                positions_[i].push_back(RandomRange::random<double>(rangeMin_[j], rangeMax_[j]));
	    }
    }

    for (size_t i = 0; i < population_; i += 1) {
	velocity_.push_back(RandomRange::random<double>(0, 1));
    }

    evaluate_();
}

void ParticleSwarmOptimizer::evaluate_() {
    for (size_t i = 0; i < positions_.size(); i += 1) {
        const double fitness__ = fitnessFunction_(positions_[i]);
        if (best_fitness_ < fitness__) {
            best_fitness_ = fitness__ ;
            best_solution_ = Solution(positions_[i]);
        }
        fitness_[i] = fitness__;
    }
}

const double ParticleSwarmOptimizer::fitnessFunction_(const Solution &solution) const {
    return fitnessFunc_(solution);
}

