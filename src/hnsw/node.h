#pragma once
#include "shared.h"


using NeighborWithDistance = std::pair<uint32_t, Distance>; // pair of node-offset and distance to owning node

// functor, a struct wrapping a function, since std::priority_queue expects a type
struct DistanceComparator {
    bool operator()(NeighborWithDistance& x, NeighborWithDistance& y) {
        return x.second < y.second;
    }
};

using NeighborQueue = std::priority_queue<NeighborWithDistance, std::vector<NeighborWithDistance>, DistanceComparator>;

class Node {
    public:
        uint32_t id;
        uint8_t highest_layer;
        std::vector<float> vector;
        std::vector<NeighborQueue> neighborQueues; // array of neighbor queues, one for each layer

        Node(uint32_t id, uint8_t highest_layer, const std::vector<float>& vector);

        void getNeighborOffsets(std::vector<std::vector<uint32_t>>& neighbor_offsets, uint8_t M);
};
