#include "metadata.h"

bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

toml::table createMetadataFile(std::string vector_index_name, uint16_t dim) {

    try {
        // create path
        std::string path;
        buildPath(&path, METADATA_FILE, &vector_index_name);

        if (!fileExists(path)) {
            toml::table config;
            config.insert("dimensions", dim);
            config.insert("global_ep_offset", 0);
            config.insert("node_id_counter", 0);
            config.insert("is_empty", 1);
            config.insert("M", DEFAULT_M);

            std::ofstream file(path);
            file << config;
        }
        else {
            fprintf(stderr, "Metadata file already exists, aborting.");
            exit(1);
        }
        return toml::parse_file(path);
    }

    catch (const toml::parse_error& err) {
        fprintf(stderr, "Failed to parse %s: %s (line %u, col %u)\n",
                vector_index_name.c_str(),
                std::string(err.description()).c_str(),
                err.source().begin.line,
                err.source().begin.column);
        exit(1);
    }
}

void updateMetadataFile(std::string& vector_index_name, index_metadata_t& metadata) {
    try {
        // create path
        std::string path;
        buildPath(&path, METADATA_FILE, &vector_index_name);

        if (fileExists(path)) {
            toml::table config;
            config.insert("global_ep_offset", metadata.global_ep_offset);
            config.insert("node_id_counter", metadata.node_id_counter);
            config.insert("is_empty", metadata.is_empty);

            std::ofstream file(path);
            file << config;
        }
        else {
            fprintf(stderr, "Critical: Metadata file does not exists, aborting.");
            exit(1);
        }
    }

    catch (const toml::parse_error& err) {
        fprintf(stderr, "Failed to parse %s: %s (line %u, col %u)\n",
                vector_index_name.c_str(),
                std::string(err.description()).c_str(),
                err.source().begin.line,
                err.source().begin.column);
        exit(1);
    }
}

toml::table loadMetadataFile(std::string vector_index_name) {

    try {
        // create path
        std::string path;
        buildPath(&path, METADATA_FILE, &vector_index_name);

        if (fileExists(path)) {
            return toml::parse_file(path);
        }
        else {
            fprintf(stderr, "Metadata file doesn't exist, aborting.");
            exit(1);
        }
    }

    catch (const toml::parse_error& err) {
        fprintf(stderr, "Failed to parse %s: %s (line %u, col %u)\n",
                vector_index_name.c_str(),
                std::string(err.description()).c_str(),
                err.source().begin.line,
                err.source().begin.column);
        exit(1);
    }
}
