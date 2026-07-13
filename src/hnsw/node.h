#pragma once
#include "shared.h"

using NeighborWithDistance = std::pair<Node, Distance>;
using NeighborQueue = std::priority_queue<NeighborWithDistance, std::vector<NeighborWithDistance>, DistanceComparator>;

// functor, a struct wrapping a function, since std::priority_queue expects a type
struct DistanceComparator {
    bool operator()(NeighborWithDistance& x, NeighborWithDistance& y) {
        return x.second < y.second;
    }
};

class Node {
    public: 
        uint32_t id;
        uint8_t highest_layer;
        std::vector<float> * vector;

        Node(uint32_t id, uint8_t highest_layer, const std::vector<float>& vector);
        NeighborQueue neighborQueue;

        void getNeighborOffsets(std::vector<uint32_t>& neighbor_offsets, uint8_t M);
};