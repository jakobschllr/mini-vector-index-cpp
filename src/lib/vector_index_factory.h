#include "../hnsw/vector_index.h"
#include "../memory/metadata.h"
#include "../memory/bin.h"
#include "../main.h"

void create_vector_store(std::string name, uint16_t vec_dim, VectorIndex * index);
void load_vector_store(std::string name, VectorIndex * index);
