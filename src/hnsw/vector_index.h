#pragma once
#include "shared.h"
#include "graph.h"
#include "../memory/metadata.h"
#include <cmath>
#include <random>
#include "../lib/mem_controller.h"

class LevelGenerator {

    /*
    - std::random_device{}() gets a random start value that can be used as seed for a pseudo random number generator (is created for example from hardware noise)
    - mt19937_64 is the pseudo-random-number generator, that creates a random number between 0 and 2^64 -1 based on the given seed
    - u = unif(0,1) decribes a random number in the interval [0,1] where the distribution is even, meaning a numbers have the same probability distribution
    - exponentials distribution (with parameter k): Random number, where small numbers are much more likely than big numbers, density-function: f(x) = k * e^(-kx) with x >= 0. The expeceted value for multiple random experiments is at 1 / k.
    - the hnsw-formula needs m_l = 1 / ln(M) therefore we can get m_l by using the exponentials distribution with k = ln(M)
    */

    public:
        explicit LevelGenerator(uint8_t M)
        :
        randNumGen(std::random_device{}()), // with each call, creates a raw random integer between 0 and 2^64 -1
        dist(std::log(static_cast<double>(M))){} // the parameter k = ln(M) is set, and the argument of the function is rand_num_gen

        uint8_t getLevel() {
            return static_cast<uint8_t>(std::floor(dist(randNumGen)));
        }

    private:
        std::mt19937_64 randNumGen;
        std::exponential_distribution<double> dist;
};

class VectorIndex {
    public:
        std::string name;
        std::unique_ptr<Graph> graph;
        index_metadata metadata;
        std::unique_ptr<LevelGenerator> level_generator;
        std::unique_ptr<MemoryController> mem_controller;

        VectorIndex();
        void init();
        int saveEmbedding(const std::vector<float>& vec, const std::string& chunk);

    private:

};
