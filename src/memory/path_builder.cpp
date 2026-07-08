#include "path_builder.h"




// build path to vector store files (vector.bin and graph.bin)
void build_path (std::string * path, file_type_e ft, std::string * name) {
    *path += VECTOR_STORE_PATH;
    *path += "/";
    *path += *name;
    *path += "/";

    switch (ft) {
        case VECTOR_FILE: {
            *path += "vector.bin";
            break;
        }
        case GRAPH_FILE: {
            *path += "graph.bin";
            break;
        }
        case METADATA_FILE: {
            *path += "metadata.toml";
            break;
        }
    }
}