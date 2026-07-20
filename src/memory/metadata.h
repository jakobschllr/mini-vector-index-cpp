#pragma once
#include "shared.h"
#include "path_builder.h"
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include "../lib/mem_controller.h"

toml::table createMetadataFile(std::string vector_index_name, uint16_t dim);
toml::table loadMetadataFile(std::string vector_index_name);
void updateMetadataFile(std::string& vector_index_name, index_metadata_t& metadata);
