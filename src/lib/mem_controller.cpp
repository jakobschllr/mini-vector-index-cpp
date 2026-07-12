#include "mem_controller.h"


// - writes node (vector) to vector.bin file
// - calculates the offset based on the Node-ID multiplied with the size of the node-data in bytes
uint32_t MemoryController::writeVector(const Node& n, uint8_t neighbor_amount) {

                         // highest_layer   
    uint32_t graph_start_offset = 1     +  n.highest_layer*     +   (n.highest_layer * neighbor_amount * 4) + 
    
    struct {
        std::vector<float> vector;
        uint32_t graph_offset; // reference to neighbor list in graph.bin
    } node_bin_data = {
        .vector = *n.vector,
        .graph_offset = graph_start_offset
    };
    
    uint32_t insert_at_offset = n.id * (n.vector->size() + 4); // + 4 bytes for graph_offset
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