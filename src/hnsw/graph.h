#include <string>
#include "node.h"
#include "../memory/shared.h"
#include "../memory/bin.h"
#include "../memory/metadata.h"
#include <memory>

/*
- mutable graph
*/
class Graph {

    private:
        uint8_t highest_layer;
        std::unique_ptr<Node> global_ep_node;
        index_metadata_t * metadata;

    public:
        // Constructor
        Graph(index_metadata_t * metadata);
};
