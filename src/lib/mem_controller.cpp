#include "mem_controller.h"
#include "../memory/metadata.h"

// returns byte offset for node-data (vector and reference to neighbor list) is written to in vector.bin
uint32_t getNodeInsertionOffset (const Node& n) {
    uint16_t node_size = n.vector->size() + 4;
    return n.id * node_size;
}

uint32_t getNeighborListInsertionOffset (const Node& n, uint8_t& M) {
                                        // highest_layer        // 1 Byte neighbor amount and                    // per Layer: neighbor-list consisting of 4-Byte-Adresses;
                                                                // 1 Byte relative startoffset for each layer    // reserving space for M * 4 Bytes, so for maximum amount of neighbors

    uint16_t graph_entry_size  =        1                       + 2 * n.highest_layer +                         + n.highest_layer * M * 4;
    return graph_entry_size * n.id;
}


// - writes node (vector) to vector.bin file
// - writes neighbors into graph.bin
void MemoryController::writeVector(Node& n, uint8_t M) { // M is maximum neighbor amount

    uint32_t node_offset = getNodeInsertionOffset(n);
    uint32_t neighbor_list_offset = getNeighborListInsertionOffset(n, M);

    // write vector data
    memcpy(this->vector_file_mapping + node_offset, n.vector->data(), n.vector->size() * sizeof(float)); // write vector data
    memcpy(this->vector_file_mapping + n.vector->size() * sizeof(float), &neighbor_list_offset, 4); // write offset of neighbor-data

    // write neighbor data
    std::vector<std::vector<uint32_t>> neighbor_offsets;

    // for each layer reserve M bytes (+ 1*M for layer 0)
    neighbor_offsets.reserve(M * n.highest_layer + M);
    n.getNeighborOffsets(neighbor_offsets, M); // get list of offsets for neighbor nodes

    // iterate over layers starting at 0 and copy neighbor offsets into mapping
    for (uint16_t layer; layer <= n.highest_layer; layer++) {
        memcpy(this->graph_file_mapping + neighbor_list_offset + layer * M, &neighbor_offsets[layer], M);
    }
}

void MemoryController::initMappings(std::string * name, bool create_new) {

    // create binary files for vectors and graph
    bin_resp_t v_data;
    bin_resp_t g_data;

    if (create_new) {
        createBin(name, VECTOR_FILE, &v_data);
        createBin(name, GRAPH_FILE, &g_data);
    }
    else {
        loadBin(name, VECTOR_FILE, &v_data);
        loadBin(name, GRAPH_FILE, &g_data);
    }

    if (!v_data.success || !g_data.success) {
        return;
    }


    this->vector_file_mapping = v_data.mapping;
    this->graph_file_mapping = g_data.mapping;
}

void MemoryController::getMetadata(index_metadata * metadata, bool create_new, std::string * name, uint16_t vec_dim) {
    toml::table metadata_toml;
    if (create_new) {
        // create metadata file on disk
        toml::table metadata_toml =  createMetadataFile(*name, vec_dim);
    }

    else {
        // load metadata file from dist
        toml::table metadata_toml =  loadMetadataFile(*name);
    }


    metadata->is_empty = metadata_toml["is_empty"].value_or<uint8_t>(1);
    metadata->dim = metadata_toml["dimensions"].value_or<uint16_t>(0);
    metadata->global_ep_offset = metadata_toml["global_ep_offset"].value_or<uint32_t>(0);
    metadata->node_id_counter = metadata_toml["node_id_counter"].value_or<uint32_t>(0);
    metadata->M = metadata_toml["M"].value_or<uint8_t>(DEFAULT_M);
}

void MemoryController::writeMetadata(index_metadata_t& metadata, std::string& index_name) {
    updateMetadataFile(index_name, metadata);
}
