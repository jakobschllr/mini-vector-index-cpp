#pragma once
#include "../main.h"
#include <fcntl.h> 
#include <unistd.h>
#include <sys/mman.h>
#include "string"

enum file_type {
    VECTOR_FILE,
    GRAPH_FILE,
    METADATA_FILE
} typedef file_type_e;