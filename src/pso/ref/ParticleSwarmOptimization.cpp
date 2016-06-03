//
//  ParticleSwarmOptimization.cpp
//  ParticleSwarmOptimization
//
//  Created by Ming on 12/3/14.
//  Copyright (c) 2014 Ming. All rights reserved.
//

#include "ParticleSwarmOptimization.h"
#include "Particle.h"
//#include "randomrange.h"
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>

ParticleSwarmOptimization::ParticleSwarmOptimization(const int particle_num, const int dimension, const double w, const double c1, const double c2):particle_num_(particle_num), dimension_(dimension), w_(w), c1_(c1), c2_(c2) {
    particles_ = std::vector<Particle>(particle_num_, Particle(dimension_));
}

void ParticleSwarmOptimization::initialize(const double min, const double max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    for (size_t i = 0; i < particle_num_; i += 1) {
        std::vector<double> tmp(k_*d_);
        for (size_t j = 0; j < k_; j += 1) {
            std::uniform_int_distribution<int> uniform_int(0, (int)data_.size()-1);
            int randam_num = uniform_int(rng);
            for (int k = 0; k < d_; k += 1) {
                tmp[j*d_+k] = data_[randam_num][k];
            }
        }
        particles_[i].setParticle(tmp);
    }
}

void ParticleSwarmOptimization::readfile(const std::string &filename) {
    std::ifstream file;
    file.open(filename.c_str());
    if (!file) {
        std::cout<< std::endl << "Error filename." << std::endl;
    }
    else{
        while( !file.eof() ){
            std::vector<double> point(4);
            char e;
            file >> point[0] >> e >> point[1] >> e >> point[2] >> e >> point[3];
            data_.push_back(point);
        }
        file.close();
    }
}

const double ParticleSwarmOptimization::fitness_(const Particle &particle) const {
    
    //calculate fitness
    std::vector<int> cluster = std::vector<int>(data_.size());
    std::vector<double> statistic = std::vector<double>(k_);
    for (std::size_t i = 0; i < data_.size(); i += 1) {
        double min_distance = INTMAX_MAX;
        for (std::size_t j = 0; j < k_; j += 1) {
            double distance = 0;
            for (std::size_t k = 0; k < d_; k += 1) {
                distance += pow(data_[i][k] - particle.at(j*d_+k), 2);
            }
            if (distance < min_distance) {
                min_distance = distance;
                cluster[i] = (int)j;
            }
        }
        statistic[cluster[i]] += sqrt(min_distance);
    }
    
    int cluster1 = 0, cluster2 = 0, cluster3 = 0;
    for (int i= 0; i < cluster.size(); i++) {
        if(cluster[i]==0) cluster1++;
        else if(cluster[i]==1) cluster2++;
        else cluster3++;
    }
    std::cout << cluster1 << " " << cluster2 << " " << cluster3 << std::endl;
    
    
    double fitness = 0;
    for (std::size_t i = 0; i < statistic.size(); i += 1) {
        fitness += statistic[i];
        //std::cout << statistic[i] << std::endl;
    }
    return fitness;
}

void ParticleSwarmOptimization::evaluate() {
    for (size_t i = 0; i < particles_.size(); i += 1) {
        double fitness = fitness_(particles_[i]);
        particles_[i].fitness(fitness);
    }
}

void ParticleSwarmOptimization::updatePBest() {
    for (size_t i = 0; i < particles_.size(); i += 1) {
        particles_[i].updatePBest();
    }
}


void ParticleSwarmOptimization::updateGBest() {
    double min = INT32_MAX;
    size_t min_index = -1;
    for (size_t i = 0; i < particles_.size(); i += 1) {
        if (particles_[i].getHistoryFitness() < min) {
            min = particles_[i].getHistoryFitness();
            min_index = i;
        }
    }
    global_best_ = particles_[min_index].getPBest();
    global_best_fitness_ = min;
}


void ParticleSwarmOptimization::updateVelocity() {
    for (size_t i = 0; i < particles_.size(); i += 1) {
        particles_[i].updateVelocity(w_, c1_, c2_, global_best_);
    }
}


void ParticleSwarmOptimization::updatePosition() {
    for (size_t i = 0; i < particles_.size(); i += 1) {
        particles_[i].updatePosition();
    }
}

void ParticleSwarmOptimization::print() const {
    std::cout << global_best_fitness_ << std::endl;
}

void ParticleSwarmOptimization::kmeans() {
    
    std::cout << "kmeans start" << std::endl;
    Particle tmp(12);
    tmp.setParticle(global_best_);
    std::cout << fitness_(tmp) << std::endl;
    bool cont = true;
    
    for (int i = 0; i < global_best_.size(); i++) {
        std::cout << global_best_[i] << " ";
    }
    std::cout << std::endl;

    
    while (cont) {
        
        std::vector<double> check(global_best_);
        
        //phase 1: clustring datas
        std::vector<int> cluster = std::vector<int>(data_.size());
        for (std::size_t i = 0; i < data_.size(); i += 1) {
            double min_distance = INTMAX_MAX;
            for (std::size_t j = 0; j < k_; j += 1) {
                double distance = 0;
                for (std::size_t k = 0; k < d_; k += 1) {
                    distance += pow(data_[i][k] - global_best_[j*d_+k], 2);
                }
                if (distance < min_distance) {
                    min_distance = distance;
                    cluster[i] = (int)j;
                }
            }
        }
        
        //phase 2: update centroids
        std::vector<double> newcentre(12);
        std::vector<int> counter = std::vector<int>(k_);
        for (std::size_t i = 0; i < cluster.size(); i += 1) {
            for (std::size_t j = 0; j < d_; j += 1) {
                newcentre[d_*cluster[i]+j] += data_[i][j];
            }
            counter[cluster[i]] += 1;
        }
        for (std::size_t i = 0; i < 12; i += 1) {
            global_best_[i] = newcentre[i]/(counter[i/d_]);
        }
        
        cont = false;
        for (std::size_t i = 0; i < 12; i += 1) {
            //std::cout << global_best_[i] << " " << check[i] << std::endl;
            if (global_best_[i] != check[i]) {
                cont = true;
            }
        }
    }
    
    tmp.setParticle(global_best_);
    std::cout << fitness_(tmp) << std::endl;

}

