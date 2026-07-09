#include "graph.h"

Graph::Graph() {
};

void Graph::update_global_ep(uint32_t id, uint8_t layer, const std::vector<float>& vec) {
    this->global_ep_node = std::make_unique<Node>(id, layer, vec);
}