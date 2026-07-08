#include "graph.h"

Graph::Graph(index_metadata_t * metadata) {

    // init graph based on metadata
    this->metadata = metadata;

    // init global ep node
    this->global_ep_node = std::make_unique<Node>(this->metadata->global_ep_offset);
};