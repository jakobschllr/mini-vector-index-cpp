#include "shared.h"
#include "path_builder.h"
#include <fstream>
#include <filesystem>
#include <sys/stat.h>

toml::table createMetadataFile(std::string vector_index_name, uint16_t dim);
toml::table loadMetadataFile(std::string vector_index_name);