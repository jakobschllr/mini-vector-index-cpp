#include "vector_index_factory.h"


void create_vector_store(std::string name, uint16_t vec_dim, VectorIndex * index) {

    index->name = name;

    // initialize memory controller
    index->mem_controller = std::make_unique<MemoryController>();

    // init metadata
    index->mem_controller->get_metadata(index->metadata, true, &name, vec_dim);

    // init memory mappings in memory controller
    index->mem_controller->init_mappings(&name, true);
};


void load_vector_store(std::string name, VectorIndex * index) {

    index->name = name;

    // initialize memory controller
    index->mem_controller = std::make_unique<MemoryController>();

    // init metadata
    index->mem_controller->get_metadata(index->metadata, false, &name, 0);
    
    // init memory mappings in memory controller
    index->mem_controller->init_mappings(&name, false);
};