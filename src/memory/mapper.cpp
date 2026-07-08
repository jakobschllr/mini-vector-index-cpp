#include "mapper.h"

// - maps file into page cache using mmap
// - uses default page size (DEFAULT_VEC_STORE_SIZE_BYTES) if no file size ist passed (int file_size)
char * get_mapping(int fd, int file_size) {
    // use mmap to map file into virtual memory of process (user space)
    char * map = (char *) mmap(
        NULL, // OS should choose memory adress in user space itself
        file_size > 0 ? file_size : DEFAULT_VEC_STORE_SIZE_BYTES, // length of mapping
        PROT_READ | PROT_WRITE, // Protection READ and Write
        MAP_SHARED, // Changes must be written back directly to file
        fd,
        0 // offset 0, start directly at
    );

    // close file descriptor
    close(fd);
    return map;
}

// unmap
void clear_map(char ** map) {
    munmap(&map, DEFAULT_VEC_STORE_SIZE_BYTES);
}