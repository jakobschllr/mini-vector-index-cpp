#pragma once
#include "shared.h"

char * get_mapping(int fd, int file_size);
void clear_map(char ** map);