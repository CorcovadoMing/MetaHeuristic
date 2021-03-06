#include "ParticleSwarmOptimizer.h"
#include "Solution.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>

void ParticleSwarmOptimizer::print() const {
    std::cout << "=== Positions ===" << std::endl;
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < positions_[i].size(); j += 1) {
	    std::cout << positions_[i][j] << " ";
	}
	std::cout << "\tVelocity: ";
        for (size_t j = 0; j < velocities_[i].size(); j += 1) {
	    std::cout << velocities_[i][j] << " ";
	}
        std::cout << "\tPBest: ";
        for (size_t j = 0; j < pbest_positions_[i].size(); j += 1) {
	    std::cout << pbest_positions_[i][j] << " ";
	}
        std::cout << "\tPBest Fitness: " << pbest_fitness_[i]; 
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

const std::vector<double> ParticleSwarmOptimizer::getResult() const {
    return best_solution_;
}

const double ParticleSwarmOptimizer::getFitness() const {
    return best_fitness_;
}

const std::vector<double> ParticleSwarmOptimizer::runWithIteration(double iter, const Parameters &param) {
    initial(param);
    for (size_t i = 0; i < iter; i += 1) {
        updateVelocity();
        updatePosition();
        evaluate_();
    }
    return getResult();
}

const std::vector<double> ParticleSwarmOptimizer::runWithDuration(double duration, const Parameters &param) {
    initial(param);
    auto start = clock();
    while (clock()/CLOCKS_PER_SEC < duration) {
        updateVelocity();
        updatePosition();
        evaluate_();
    }   
    return getResult();
}

void ParticleSwarmOptimizer::updateVelocity() {
    const double c1_rand = RandomRange::random<double>(0, 1);
    const double c2_rand = RandomRange::random<double>(0, 1);
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < velocities_[i].size(); j += 1) {
            velocities_[i][j] = (w_ * velocities_[i][j]) + (c1_ * c1_rand * (pbest_positions_[i][j] - positions_[i][j])) + (c2_ * c2_rand * (best_solution_[j] - positions_[i][j]));
        }
    }    
}

void ParticleSwarmOptimizer::updatePosition() {
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < positions_[i].size(); j += 1) {
            if (j < int_index_) {
                positions_[i][j] = std::max(std::min(int(positions_[i][j] + velocities_[i][j]), int(rangeMax_[j])), int(rangeMin_[j]));
            }
            else {
                positions_[i][j] = std::max(std::min(positions_[i][j] + velocities_[i][j], rangeMax_[j]), rangeMin_[j]);
            }
        }
    }
} 

void ParticleSwarmOptimizer::initial(const Parameters &Param) {
    rangeMax_ = Param.RangeMax;
    rangeMin_ = Param.RangeMin;
    fitnessFunc_ = Param.FitnessFunction;
    best_fitness_ = INT32_MIN;
    int_index_ = Param.DimensionsInt;
    population_ = Param.Populations;
    w_ = Param.w;
    c1_ = Param.c1;
    c2_ = Param.c2;

    const int dimension = Param.Dimensions;

    positions_ = std::vector<Solution>(population_, Solution());
    velocities_ = std::vector<Solution>(population_, Solution());
    fitness_ = std::vector<double>(population_, 0);
    pbest_fitness_ = std::vector<double>(population_, 0);
    for (size_t i = 0; i < population_; i += 1) {
        for (size_t j = 0; j < dimension; j += 1) {
            if (j < int_index_)
                positions_[i].push_back(RandomRange::random<int>(rangeMin_[j], rangeMax_[j]));
            else
                positions_[i].push_back(RandomRange::random<double>(rangeMin_[j], rangeMax_[j]));
            velocities_[i].push_back(RandomRange::random<double>(-rangeMax_[j], rangeMax_[j]));
	}
    }

    pbest_positions_ = positions_;
    evaluate_();
}

void ParticleSwarmOptimizer::evaluate_() {
    for (size_t i = 0; i < positions_.size(); i += 1) {
        const double fitness__ = fitnessFunction_(positions_[i]);
        if (best_fitness_ < fitness__) {
            best_fitness_ = fitness__ ;
            best_solution_ = Solution(positions_[i]);
        }
        if (pbest_fitness_[i] <= fitness__) {
            pbest_fitness_[i] = fitness__;
            pbest_positions_[i] = positions_[i];
        } 
        fitness_[i] = fitness__;
    }
}

const double ParticleSwarmOptimizer::fitnessFunction_(const Solution &solution) const {
    return fitnessFunc_(solution);
}

