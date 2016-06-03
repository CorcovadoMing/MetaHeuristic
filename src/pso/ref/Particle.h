//
//  Particle.h
//  ParticleSwarmOptimization
//
//  Created by Ming on 12/3/14.
//  Copyright (c) 2014 Ming. All rights reserved.
//

#ifndef __ParticleSwarmOptimization__Particle__
#define __ParticleSwarmOptimization__Particle__

#include <vector>

class Particle {
public:
    Particle(const int);
    void randomize(const double, const double);
    double at(const size_t index) const { return particle_[index]; }
    void at(const size_t index, const double data) { particle_[index] = data; }
    double getHistoryFitness() const { return history_fitness_; }
    std::vector<double> getPBest() const { return history_; }
    void fitness(const double fitness) { fitness_ = fitness; }
    void updatePBest();
    void updateVelocity(const double, const double, const double, const std::vector<double> &);
    void updatePosition();
    void print() const;
    void setParticle(std::vector<double> &particle) { particle_ = particle; }
    std::vector<double> &getParticle() { return particle_; }
private:
    std::vector<double> particle_, velocity_, history_;
    double fitness_, history_fitness_ = INTMAX_MAX;
};

#endif /* defined(__ParticleSwarmOptimization__Particle__) */
