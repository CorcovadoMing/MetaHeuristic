//
//  ParticleSwarmOptimization.h
//  ParticleSwarmOptimization
//
//  Created by Ming on 12/3/14.
//  Copyright (c) 2014 Ming. All rights reserved.
//

#ifndef __ParticleSwarmOptimization__ParticleSwarmOptimization__
#define __ParticleSwarmOptimization__ParticleSwarmOptimization__

#include <vector>
#include "Particle.h"

class ParticleSwarmOptimization {
public:
    ParticleSwarmOptimization(const int, const int, const double w, const double c1, const double c2);
    void setw(const double w) { w_ = w; }
    void initialize(const double, const double);
    void readfile(const std::string &);
    void evaluate();
    void updatePBest();
    void updateGBest();
    void updateVelocity();
    void updatePosition();
    void kmeans();
    void print() const;
private:
    const double fitness_(const Particle &) const;
    
    const int k_ = 3, d_ = 4;
    const int particle_num_, dimension_;
    double w_, c1_, c2_;
    std::vector<Particle> particles_;
    std::vector<double> global_best_;
    double global_best_fitness_;
    std::vector< std::vector<double> > data_;
};

#endif /* defined(__ParticleSwarmOptimization__ParticleSwarmOptimization__) */
