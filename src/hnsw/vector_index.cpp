#include "vector_index.h"


void VectorIndex::init() {
    // initialize graph based on this->metadata
    this->graph  = std::make_unique<Graph>(this->metadata);
    this->level_generator = std::make_unique<LevelGenerator>(this->metadata->M);
}

int VectorIndex::saveEmbedding(const std::vector<float>& vec, const std::string& chunk) {

    // TODO: save the chunk in the data-file using the node-id and key-value-loopup index


    // Calculate highest layer for new node
    uint16_t l = this->level_generator->getLevel();
    
    // if index is empty save the first embedding
    if (this->metadata->is_empty) {
        
        this->graph->updateGlobalEp(this->metadata->node_id_counter, l, vec);
        uint32_t globale_ep_offset = this->mem_controller->write_vector(*this->graph->global_ep_node, this->metadata->M);

        // update metadata
        this->metadata->node_id_counter++;
        this->metadata->global_ep_offset = globale_ep_offset;
        this->metadata->highest_layer = l;
        this->metadata->is_empty = 0;

        // write back metadata using memory controller

    }

    // index isn't empty, add node
    else {

        // create global entrypoint
        

        // if node-layer is the highest, update highest-layer in metadata and update global entry point

    }


    // Increment Node-ID


    // Write back metadata to memory


    return 0;
}