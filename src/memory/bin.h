#pragma once
#include "mapper.h"
#include "shared.h"

struct bin_resp {
    char * mapping;
    bool is_empty;
    bool success;
} typedef bin_resp_t;

void load_bin(std::string * name, file_type_e ft, bin_resp_t * bin_data);
void create_bin(std::string * name, file_type_e ft, bin_resp_t * bin_data);