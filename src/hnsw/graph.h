#pragma once
#include "node.h"
#include "../memory/shared.h"
#include "../memory/bin.h"
#include "../memory/metadata.h"
#include "../lib/mem_controller.h"
#include <memory>
#include "shared.h"

struct CosineSimilarity {
    static float calc(const std::vector<float>& a, const std::vector<float>& b) {


        return 0.0f;
    }
};

struct L2_Distance {
    static float calc(const std::vector<float>& a, const std::vector<float>& b) {

        return 0.0f;
    }
};

struct HammingDistance {
    static uint32_t calc(const std::vector<float>& a, const std::vector<float>& b) {

        return 0;
    }
};

template<typename dist_metric>
class Graph {
    public:
        // Constructor
        Graph();
        Node* global_ep_node;
        void updateGlobalEp(uint32_t id, uint8_t layer, const std::vector<float>& vec);
        void descentGraphForInsert(uint8_t l,  uint8_t L, const std::vector<float>& q, const uint32_t global_ep_offset);
        void getNNOnLayer(const std::vector<float>& q, const uint32_t current_ep_offset, const uint8_t layer, uint32_t * nn);
};
