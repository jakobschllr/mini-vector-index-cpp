#pragma once
#include "shared.h"

char * getMapping(int fd, int file_size);
void clearMap(char ** map);