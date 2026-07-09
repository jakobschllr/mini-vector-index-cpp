#include "mem_controller.h"



void MemoryController::save_global_ep(Node * ep, Graph * g) {

}

void MemoryController::init_mappings(std::string * name, bool create_new) {

    // create binary files for vectors and graph 
    bin_resp_t v_data;
    bin_resp_t g_data;
    
    if (create_new) {
        create_bin(name, VECTOR_FILE, &v_data);
        create_bin(name, GRAPH_FILE, &g_data);
    }
    else {
        load_bin(name, VECTOR_FILE, &v_data);
        load_bin(name, GRAPH_FILE, &g_data);
    }

    if (!v_data.success || !g_data.success) {
        return;
    }


    this->vector_file_mapping = v_data.mapping;
    this->graph_file_mapping = g_data.mapping;
}


void MemoryController::get_metadata(index_metadata * metadata, bool create_new, std::string * name, uint16_t vec_dim) {

    if (create_new) {
        // create metadata file on disk
        toml::table metadata_toml =  create_metadata_file(*name, vec_dim);
    }

    else {
        // load metadata file from dist
        toml::table metadata_toml =  load_metadata_file(*name);
    }

    
    metadata->is_empty = metadata_toml["is_empty"].value_or<uint8_t>(1);
    metadata->dim = metadata_toml["dimensions"].value_or<uint16_t>(0);
    metadata->global_ep_offset = metadata_toml["global_ep_offset"].value_or<uint32_t>(0);
    metadata->node_id_counter = metadata_toml["node_id_counter"].value_or<uint32_t>(0);
    metadata->M = metadata_toml["M"].value_or<uint8_t>(DEFAULT_M);
}