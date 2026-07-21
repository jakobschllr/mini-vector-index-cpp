#include "vector_index.h"


void VectorIndex::init() {
    // initialize graph based on this->metadata
    this->graph  = std::make_unique<Graph>();
    this->level_generator = std::make_unique<LevelGenerator>(this->metadata.M);
}

int VectorIndex::saveEmbedding(const std::vector<float>& vec, const std::string& chunk) {

    // TODO: save the chunk in the data-file using the node-id and key-value-loopup index


    // Calculate highest layer for new node
    uint16_t l = this->level_generator->getLevel();

    // if index is empty save the first embedding
    if (this->metadata.is_empty) {

        this->graph->updateGlobalEp(this->metadata.node_id_counter, l, vec);

        // write vector and graph data
        this->mem_controller->writeVector(*this->graph->global_ep_node, this->metadata.M);

        // update metadata
        this->metadata.node_id_counter++;
        this->metadata.global_ep_offset = 0;
        this->metadata.highest_layer = l;
        this->metadata.is_empty = 0;

        // write back metadata
        this->mem_controller->writeMetadata(this->metadata, this->name);

    }

    // index isn't empty, add node
    else {

        this->graph->descentGraphForInsert(l, this->metadata.highest_layer, vec);

        this->metadata.node_id_counter++;

    }

    return 0;
}
