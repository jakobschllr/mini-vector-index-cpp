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
        std::unique_ptr<Node> global_ep_node;
        void updateGlobalEp(uint32_t id, uint8_t layer, const std::vector<float>& vec);
        void descentGraphForInsert(uint8_t l,  uint8_t L, const std::vector<float>& q);
        std::unique_ptr<Node> getClosestNeighborOnLayer(const std::vector<float>& q, uint8_t layer);
};


Graph::Graph() {
};

void Graph::updateGlobalEp(uint32_t id, uint8_t layer, const std::vector<float>& vec) {
    this->global_ep_node = std::make_unique<Node>(id, layer, vec);
}

std::unique_ptr<Node> Graph::getClosestNeighborOnLayer(const std::vector<float>& q, uint8_t layer) {

    // TODO: graph must get distance metric on init for getting closest neighbor here

    // find closest neighbor using heuristic and return Node-Object for neighbor
}

void Graph::descentGraphForInsert(uint8_t l, uint8_t L, const std::vector<float>& q) {


    if (l < L) {

        std::pair<std::unique_ptr<Node>, uint8_t> ep; // current entrypoint node and current layer
        ep.first = this->global_ep_node;
        ep.second = L;

        while (ep.second > l) {

            ep.first = this->getClosestNeighborOnLayer(q, ep.second);



            ep.second--;
        }

    }

    // l >= L
    else {

    }
}
