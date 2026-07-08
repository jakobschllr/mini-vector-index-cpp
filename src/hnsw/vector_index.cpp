#include "vector_index.h"

void VectorIndex::init_graph() {
    // initialize graph based on this->metadata
    this->graph  = std::make_unique<Graph>(this->metadata);
}
