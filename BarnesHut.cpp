#include "OctTree.h"
#include "Timer.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "Node.h"
#include "Body.h"

constexpr bool DEBUG = true;
constexpr int DELTA = 1;

int main(int argc, char *argv[]) {
    int numParticles = 0;
    int steps = 0;

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            numParticles = std::atoi(argv[i + 1]);
        } 
        else if (std::strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            steps = std::atoi(argv[i + 1]);
        }
    }

    if (numParticles <= 0 || steps <= 0) {
        std::cerr << "Usage: ./BarnesHut -n <number_of_particles> -s <number_of_steps>" << std::endl;
        exit(-1);
    }

    if (DEBUG) {
        std::cout << "Simulation Steps: " << steps << std::endl;
        std::cout << "Number of Particles: " << numParticles << std::endl;
    }

    vector_3d lowerBound = std::make_tuple(0, 0, 0);
    vector_3d upperBound = std::make_tuple(10000, 10000, 10000);

    std::vector<Leaf *> particles(numParticles);
    for (int i = 0; i < numParticles; i++) {
        Body body(10, 1, 1, 1, 10, 10, 10);
        particles[i] = new Leaf(nullptr, std::move(body));
    }

    Timer timer = Timer();
    timer.start();

    OctTree tree = OctTree(particles, lowerBound, upperBound);
    tree.setCenterOfMass();

    std::vector<double> stepTimes(steps);
    for (int i = 0; i < steps; i++) {
        Timer stepTimer = Timer();
        stepTimer.start();
        //#pragma omp parallel for
        for (int j = 0; j < numParticles; j++) {
            vector_3d f = tree.treeForce(particles[j]);
            particles[j]->body.apply(f);
        }
        //#pragma omp parallel for
        for (int j = 0; j < numParticles; j++) {
            particles[j]->body.move(DELTA);
        }
        tree.setCenterOfMass();
        stepTimer.stop();
        stepTimes[i] = stepTimer.duration();
    }

    timer.stop();

    double minTime = std::numeric_limits<double>::max();
    double maxTime = std::numeric_limits<double>::min();
    double totalTime = 0.0;

    for (double t : stepTimes) {
        if (t < minTime) minTime = t;
        if (t > maxTime) maxTime = t;
        totalTime += t;
    }

    double avgTime = totalTime / steps;

    minTime /= 1000.0;
    maxTime /= 1000.0;
    avgTime /= 1000.0;

    std::cout << std::left
              << std::setw(4) << "min" 
              << std::setw(4) << "max" 
              << std::setw(4) << "avg" 
              << std::fixed << std::setprecision(6) 
              << std::setw(15) << minTime 
              << std::setw(15) << maxTime 
              << std::setw(15) << avgTime 
              << std::endl;

    for (auto &particle : particles) delete particle;

    return 0;
}
