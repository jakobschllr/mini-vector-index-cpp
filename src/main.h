#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "./external/toml.hpp"
#include <utility>
#include <queue>
#include <vector>

#define VECTOR_STORE_PATH "/Users/jakobschiller/.1_bit_mini_vec"
#define DEFAULT_VEC_STORE_SIZE_BYTES 50 * 1024 * 1024 // 50 MB
#define DEFAULT_M 20

#ifndef VEC_DIM
#define VEC_DIM 1024
#endif

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif
