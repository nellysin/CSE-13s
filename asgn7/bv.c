#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "bv.h"

//CITE: Professor Long for bitvector code in comments repo in bv8.h
//CITE: TA Eugene for further instructions in assignment doc

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) { //creating and initializing for the struct
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        uint32_t bytes = (length / 8) + (length / 8 ? 1 : 0);
        bv->vector = (uint8_t *) calloc(bytes, sizeof(uint8_t));
        bv->length = length;
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    if (*bv) { //deleting the bit vector
        free(*bv);
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length; //returning the length of bit vector
}

bool bv_set_bit(BitVector *bv, uint32_t i) { //setting to the bit vector
    if (i < bv->length) { //make sure i is in range
        bv->vector[i / 8] |= (0x1 << i % 8);
        return true;
    } else {
        return false;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) { //clearing the bit vector to 0
    if (i < bv->length) { //make sure i is in range
        bv->vector[i / 8] &= ~(0x1 << i % 8);
        return true;
    } else {
        return false;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) { //boolean logic getting the bit of 0 and 1
    if (i < bv->length) { //make sure i is in range
        return (bv->vector[i / 8] >> i % 8) & 0x1;
    }
    return false;
}

void bv_print(BitVector *bv);
