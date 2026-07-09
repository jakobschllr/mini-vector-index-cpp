#include "vector_index_factory.h"


void create_vector_store(std::string name, uint16_t vec_dim, VectorIndex * index) {

    // create metadata file
    toml::table metadata =  create_metadata_file(name, vec_dim);

    // create binary files for vectors and graph 
    bin_resp_t v_data;
    bin_resp_t g_data;
    create_bin(&name, VECTOR_FILE, &v_data);
    create_bin(&name, GRAPH_FILE, &g_data);

    if (!v_data.success || !g_data.success) {
        return;
    }

    index->name = name;
    index->metadata->is_empty = metadata["is_empty"].value_or<uint8_t>(1);
    index->metadata->dim = metadata["dimensions"].value_or<uint16_t>(0);
    index->metadata->global_ep_offset = metadata["global_ep_offset"].value_or<uint32_t>(0);
    index->metadata->node_id_counter = metadata["node_id_counter"].value_or<uint32_t>(0);
    index->metadata->M = metadata["M"].value_or<uint8_t>(DEFAULT_M);
    index->metadata->v_map = v_data.mapping;
    index->metadata->g_map = g_data.mapping;
};


void load_vector_store(std::string name, VectorIndex * index) {

    // load metadata file
    toml::table metadata =  load_metadata_file(name);

    // load binary data for vectors and graph from file
    bin_resp_t v_data;
    bin_resp_t g_data;
    load_bin(&name, VECTOR_FILE, &v_data);
    load_bin(&name, GRAPH_FILE, &g_data);

    if (!v_data.success || !g_data.success) {
        return;
    }

    index->name = name;
    index->metadata->is_empty = index->metadata->is_empty = metadata["is_empty"].value_or<uint8_t>(1);;
    index->metadata->dim = metadata["dimensions"].value_or<uint16_t>(0);
    index->metadata->global_ep_offset = metadata["global_ep_offset"].value_or<uint32_t>(0);
    index->metadata->node_id_counter = metadata["node_id_counter"].value_or<uint32_t>(0);
    index->metadata->M = metadata["M"].value_or<uint8_t>(DEFAULT_M);
    index->metadata->v_map = v_data.mapping;
    index->metadata->g_map = g_data.mapping;
};