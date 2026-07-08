#pragma once
#include "../main.h"

#ifndef VEC_DIM
#define VEC_DIM 1024
#endif

struct bit_vector {
    uint8_t data[VEC_DIM >> 3]; // if the input vector has 1024 dimension (aka 1024 32-Bit-Floats), data needs to have 1024 Bit, aka 1024 >> 3 Bytes
    char * chunk_addr; // the adress of the chunk-string (the text contents)
    size_t chunk_length; // the length of the chunk in Bytes
} typedef bit_vector_t;


bit_vector_t * transform_to_bit_vector(float * origin);