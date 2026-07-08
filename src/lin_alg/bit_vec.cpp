
#include "bit_vec.h"

/*
Receives a float32 vector `origin` with dimension VEC_DIM and returns pointer to
bit-vector with equal dimension.
*/

bit_vector_t * transform_to_bit_vector(float * origin) {
    
    bit_vector * vec = (bit_vector *) malloc(VEC_DIM);
    uint8_t bit_idx = 0;

    size_t i=0;
    for (; i<VEC_DIM;) {
        if (origin[i] >= 0.0f) {
            vec->data[i] |= 0x01 << (7-bit_idx);
        }
        else {
            vec->data[i] &= ~(0x01 << (7-bit_idx));
        }
        bit_idx = (bit_idx+1)&7;
        if (!bit_idx)
            i++;
    }

    #if DEBUG_MODE
        printf("[DEBUG]     Transformed Bit Vector: \n");
        bit_idx = 0;
        i=0;
        for (;i<VEC_DIM; i++) {
            uint8_t bit = (vec->data[i] & (0x01 << (7-bit_idx))) > 0 ? 1 : 0;
            printf("%d ", bit);
        }
        bit_idx = (bit_idx+1)&7;
        if (!bit_idx)
            i++;
    #endif

    return vec;
}