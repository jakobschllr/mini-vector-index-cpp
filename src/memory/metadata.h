#include "shared.h"
#include "path_builder.h"
#include <fstream>
#include <filesystem>
#include <sys/stat.h>

struct index_metadata {
    uint16_t dim;
    uint32_t global_ep_offset;
    char * v_map;
    char * g_map;
} typedef index_metadata_t;

toml::table create_metadata_file(std::string vector_index_name, uint32_t dim);
toml::table load_metadata_file(std::string vector_index_name);