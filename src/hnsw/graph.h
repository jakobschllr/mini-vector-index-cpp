#pragma once
#include <string>
#include "node.h"
#include "../memory/shared.h"
#include "../memory/bin.h"
#include "../memory/metadata.h"
#include "../lib/mem_controller.h"
#include <memory>

/*
- mutable graph
*/
class Graph {
    public:
        // Constructor
        Graph();
        uint8_t highest_layer;
        std::unique_ptr<Node> global_ep_node;
        void update_global_ep(uint32_t id, uint8_t layer, const std::vector<float>& vec);
};
