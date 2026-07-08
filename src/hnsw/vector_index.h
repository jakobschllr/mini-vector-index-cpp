#include "shared.h"
#include "graph.h"
#include "../memory/metadata.h"

class VectorIndex {
    public:
        std::string name;
        std::unique_ptr<Graph> graph;
        bool is_empty;
        index_metadata * metadata;
        VectorIndex();
        void init_graph();
};