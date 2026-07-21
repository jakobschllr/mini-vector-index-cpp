#include "graph.h"



Graph::Graph() {
};

void Graph::updateGlobalEp(uint32_t id, uint8_t layer, const std::vector<float>& vec) {
    this->global_ep_node = new Node(id, layer, vec);
}

void Graph::getNNOnLayer(const std::vector<float>& q, const uint32_t current_ep_offset, const uint8_t layer, uint32_t * nn) {

    // TODO: graph must get distance metric on init for getting closest neighbor here
    // load node data on-demand from node mapping, store it in *nn

    // find closest neighbor using heuristic and return Node-Object for neighbor
}

void Graph::descentGraphForInsert(uint8_t l, uint8_t L, const std::vector<float>& q, const uint32_t global_ep_offset) {


    if (l < L) {

        std::pair<uint32_t, uint8_t> ep; // current entrypoint-node-offset and current layer
        ep.first = global_ep_offset;
        ep.second = L;

        while (ep.second > l) {
            uint32_t nn;
            this->getNNOnLayer(q, ep.first, ep.second, &nn);



            ep.second--;
        }

    }

    // l >= L
    else {

    }
}
