#include "shared.h"
#include "path_builder.h"
#include <fstream>
#include <filesystem>
#include <sys/stat.h>

toml::table create_metadata_file(std::string vector_index_name, uint16_t dim);
toml::table load_metadata_file(std::string vector_index_name);