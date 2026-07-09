#include "shared.h"
#include "path_builder.h"
#include <fstream>
#include <filesystem>
#include <sys/stat.h>

struct index_metadata {
    uint16_t dim; // vector dimension
    uint32_t global_ep_offset; // adress of global entrypoint in vectors.bin
    uint8_t highest_layer; // current highest layer
    uint8_t is_empty; // flag
    uint32_t node_id_counter; // counter for node IDs
    uint8_t M; // maximum amount of neighbors per node
    char * v_map; // mapping of vector.bin
    char * g_map; // mapping of graph.bin
} typedef index_metadata_t;

toml::table create_metadata_file(std::string vector_index_name, uint16_t dim);
toml::table load_metadata_file(std::string vector_index_name);