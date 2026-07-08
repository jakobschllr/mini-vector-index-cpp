#include "bin.h"
#include <sys/stat.h>
#include "path_builder.h"


// loads existing vector-store-file; maps it into page cache and returns pointer to map
void load_bin(std::string * name, file_type_e ft, bin_resp_t * bin_data) {

    // create path
    std::string path;
    build_path(&path, ft, name);

    #if DEBUG_MODE
    printf("[DEBUG]     Loading Vector Store at:\n");
    printf("[DEBUG]     %s\n", path);
    #endif

    // create file descriptor
    int fd = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644); // ReadWrite, Create file if not existing
    if (fd == -1) {
        perror("[ERROR]     Error while creating vector store file.\n");
        *bin_data = (bin_resp_t) {NULL, 0, 0};
        return;
    }

    // get file size
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("[ERROR]     Error while loading vector store file.\n");
        close(fd);
        *bin_data = (bin_resp_t) {NULL, 0, 0};
        return;
    }

    *bin_data = (bin_resp_t) {get_mapping(fd, sb.st_size), sb.st_size==0, 1};
    return;
}

// creates new empty vector-store-file; maps it into page cache and returns pointer to map
void create_bin(std::string * name, file_type_e ft, bin_resp_t * bin_data) {
    
    // create path
    std::string path;
    build_path(&path, ft, name);
    
    #if DEBUG_MODE
    printf("[DEBUG]     Creating new Vector Store at:\n");
    printf("[DEBUG]     %s\n", path);
    #endif

    // create file descriptor
    int fd = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644); // ReadWrite, Create file if not existing
    if (fd == -1) {
        perror("[ERROR]     Error while loading / creating vectore store file.\n");
        *bin_data = (bin_resp_t) {NULL, 0, 0};
        return;
    }

    // set size of file
    if (ftruncate(fd, DEFAULT_VEC_STORE_SIZE_BYTES) == -1) {
        perror("[ERROR]     Error while setting vector file size.\n");
        *bin_data = (bin_resp_t) {NULL, 0, 0};
        close(fd);
        return;
    }

    *bin_data = (bin_resp_t) {get_mapping(fd, 0), 1, 1};
    return;
}
