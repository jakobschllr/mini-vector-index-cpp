#include "vector_index.h"


void VectorIndex::init() {
    // initialize graph based on this->metadata
    this->graph  = std::make_unique<Graph>(this->metadata);
    this->level_generator = std::make_unique<LevelGenerator>(this->metadata->M);

}

int VectorIndex::save_embedding(const std::vector<float>& vec, const std::string& chunk) {

    // TODO: save the chunk in the data-file using the node-id and key-value-loopup index


    // Calculate highest layer for new node
    uint16_t l = this->level_generator->get_level();
    
    // if index is empty save the first embedding
    if (this->metadata->is_empty) {

        



    }

    // index isn't empty, add node
    else {

    }


    // Increment Node-ID


    // if node-layer is the highest, update highest-layer in metadata and update global entry point



    // Write back metadata to memory


    return 0;
}