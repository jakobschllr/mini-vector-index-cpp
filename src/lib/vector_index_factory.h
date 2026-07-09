#include "../hnsw/vector_index.h"
#include "mem_controller.h"
#include "../main.h"

void create_vector_store(std::string name, uint16_t vec_dim, VectorIndex * index);
void load_vector_store(std::string name, VectorIndex * index);
