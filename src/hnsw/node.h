#pragma once
#include "shared.h"

class Node {
    public: 
        uint32_t id;
        uint8_t highest_layer;
        std::vector<float> * vector;

        Node(uint32_t id, uint8_t highest_layer, const std::vector<float>& vector);
        void getNeighbors();
};