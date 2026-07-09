#include "graph.h"

Graph::Graph(index_metadata_t * metadata) {
    // init graph based on metadata
    this->metadata = metadata;
};

// Sets the global entry point node for the graph object (no memory operation only node-initialization for global ep)
void Graph::set_global_ep(uint32_t offset, uint8_t highest_layer) {
    this->global_ep_node = std::make_unique<Node>(offset, highest_layer);
    this->highest_layer = highest_layer;
};