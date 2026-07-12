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
        void updateGlobalEp(uint32_t id, uint8_t layer, const std::vector<float>& vec);
};


Graph::Graph() {
};

void Graph::updateGlobalEp(uint32_t id, uint8_t layer, const std::vector<float>& vec) {
    this->global_ep_node = std::make_unique<Node>(id, layer, vec);
}