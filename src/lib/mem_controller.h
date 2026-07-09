#include "../main.h"
#include "../hnsw/node.h"
#include "../memory/metadata.h"
#include "../memory/bin.h"

struct index_metadata {
    uint16_t dim; // vector dimension
    uint32_t global_ep_offset; // adress of global entrypoint in vectors.bin
    uint8_t highest_layer; // current highest layer
    uint8_t is_empty; // flag
    uint32_t node_id_counter; // counter for node IDs
    uint8_t M; // maximum amount of neighbors per node
} typedef index_metadata_t;

// acts as a translator between Objects (Node, Graph, VectorStore etc.) and (binary) files. 
class MemoryController {
    private:
        char * vector_file_mapping;
        char * graph_file_mapping;

    public:
        MemoryController();
        void get_metadata(index_metadata * metadata, bool create_new, std::string * name, uint16_t vec_dim);
        void init_mappings(std::string * name, bool create_new);
        uint32_t write_vector(const Node& n, uint8_t neighbor_amount);
};