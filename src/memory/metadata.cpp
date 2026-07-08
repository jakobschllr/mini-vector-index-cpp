#include "metadata.h"

bool file_exists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

toml::table create_metadata_file(std::string vector_index_name, uint16_t dim) {

    // create path
    std::string path;
    build_path(&path, METADATA_FILE, &vector_index_name);

    if (!file_exists(path)) {
        toml::table config;
        config.insert("dimensions", dim);
        config.insert("global_ep_offset", 0);

        std::ofstream file(path);
        file << config;
    }
    else {
        perror("Metadata file already exists, aborting.");
    }
    return toml::parse_file(path);
    
}


toml::table load_metadata_file(std::string vector_index_name) {

    // create path
    std::string path;
    build_path(&path, METADATA_FILE, &vector_index_name);

    if (file_exists(path)) {
        return toml::parse_file(path);
    }
    else {
        perror("Metadata file doesn't exist, aborting.");
    }
}