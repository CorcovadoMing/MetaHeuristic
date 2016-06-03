//
//  Particle.cpp
//  ParticleSwarmOptimization
//
//  Created by Ming on 12/3/14.
//  Copyright (c) 2014 Ming. All rights reserved.
//

#include "Particle.h"
#include <vector>
#include <iostream>
#include "randomrange.h"


Particle::Particle(const int dimension) {
    particle_ = std::vector<double>(dimension, 0.0);
    velocity_ = std::vector<double>(dimension, 0.0);
}

void Particle::randomize(const double min, const double max) {
    for (size_t i = 0; i < particle_.size(); i += 1) {
        particle_[i] = RandomRange::random<double>(min, max);
        velocity_[i] = RandomRange::random<double>(min, max);
    }
}

void Particle::print() const {
    for (const auto i : particle_) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void Particle::updatePBest() {
    if (fitness_ < history_fitness_) {
        history_fitness_ = fitness_;
        history_ = particle_;
    }
}

void Particle::updateVelocity(const double w, const double c1, const double c2, const std::vector<double> &gbest) {
    const double c1_rand = RandomRange::random<double>(0.0, 1.0);
    const double c2_rand = RandomRange::random<double>(0.0, 1.0);
    for (size_t i = 0; i < velocity_.size(); i += 1) {
        velocity_[i] = w * velocity_[i] + c1 * c1_rand * (history_[i] - particle_[i]) +
        c2 * c2_rand * (gbest[i] - particle_[i]);
        if(velocity_[i] > 2) velocity_[i] = 2;
        if(velocity_[i] < -2) velocity_[i] = -2;
    }
}

void Particle::updatePosition() {
    for (size_t i = 0; i < particle_.size(); i += 1) {
        particle_[i] = particle_[i] + velocity_[i];
        if(particle_[i] > 8) particle_[i] = 8;
        if(particle_[i] < 0) particle_[i] = 0;
    }
}




