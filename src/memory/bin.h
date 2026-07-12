#pragma once
#include "mapper.h"
#include "shared.h"

struct bin_resp {
    char * mapping;
    bool is_empty;
    bool success;
} typedef bin_resp_t;

void loadBin(std::string * name, file_type_e ft, bin_resp_t * bin_data);
void createBin(std::string * name, file_type_e ft, bin_resp_t * bin_data);