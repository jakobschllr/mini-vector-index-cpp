#include "graph.h"

Graph::Graph(index_metadata_t * metadata) {

    // init graph based on metadata
    this->metadata = metadata;


    if (!this->metadata->is_empty) {
        // init global ep node (if index isn't empty)
        this->global_ep_node = std::make_unique<Node>(this->metadata->global_ep_offset);
    }
    
};