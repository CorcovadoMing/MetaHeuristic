//
//  main.cpp
//  ParticleSwarmOptimization
//
//  Created by Ming on 12/2/14.
//  Copyright (c) 2014 Ming. All rights reserved.
//

#include <iostream>
#include "ParticleSwarmOptimization.h"

int main(int argc, const char * argv[]) {
    double w = 1.0;
    ParticleSwarmOptimization pso(30, 12 /* n * k */ , w, 2, 2);
    pso.readfile("Iris.txt");
    pso.initialize(0.0, 10.0);
    int times = 500;
    while (times--) {
        pso.setw(w*(times/500.0));
        pso.evaluate();
        pso.updatePBest();
        pso.updateGBest();
        pso.updateVelocity();
        pso.updatePosition();
        //pso.print();
    }
    pso.kmeans();
    return 0;
}
