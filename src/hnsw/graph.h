#pragma once
#include "node.h"
#include "../memory/shared.h"
#include "../memory/bin.h"
#include "../memory/metadata.h"
#include "../lib/mem_controller.h"
#include <memory>
#include "shared.h"

/*
- mutable graph
*/
class Graph {
    public:
        // Constructor
        Graph();
        Node* global_ep_node;
        void updateGlobalEp(uint32_t id, uint8_t layer, const std::vector<float>& vec);
        void descentGraphForInsert(uint8_t l,  uint8_t L, const std::vector<float>& q, const uint32_t global_ep_offset);
        void getNNOnLayer(const std::vector<float>& q, const uint32_t current_ep_offset, const uint8_t layer, uint32_t * nn);
};
