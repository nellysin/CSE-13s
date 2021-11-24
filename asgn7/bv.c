#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "bv.h"

//CITE: Professor Long for code comments repo in bv8
//CITE: TA Eugene for further instructions in assignment doc

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        uint32_t bytes = (length / 8) + (length / 8 ? 1 : 0);
        bv->vector = (uint8_t *) calloc(bytes, sizeof(uint8_t));
        bv->length = length;
        return bv;
    } else {
        return (BitVector *) 0;
    }
}

void bv_delete(BitVector **bv) {
    if (*bv) {
        free(*bv);
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        bv->vector[i / 8] |= (0x1 << i % 8);
        return true;
    } else {
        return false;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        bv->vector[i / 8] &= ~(0x1 << i % 8);
        return true;
    } else {
        return false;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        (bv->vector[i / 8] >> k % 8) & 0x1;
        return true;
    } else {
        return false;
    }
}

void bv_print(BitVector *bv);
