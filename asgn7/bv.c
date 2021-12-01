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

//constructor for a bit vector that holds length bits. In the even that sufficient memory cannot be allocated
//the function must return null or else if returns the bit vector
BitVector *bv_create(uint32_t length) { //creating and initializing for the struct
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        uint32_t bytes = (length / 8) + (length / 8 ? 1 : 0);
        bv->vector = (uint8_t *) calloc(bytes, sizeof(uint8_t));
        bv->length = length;
    }
    return bv;
}

//this is the destructor for bit vector, setting the pointer to NULL after the memory is freed
void bv_delete(BitVector **bv) {
    if (*bv) { //deleting the bit vector
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length; //returning the length of bit vector
}

//the ith bit in the bit vector. If i is out of range return false
//else return true as it indicates success of setting the bit
bool bv_set_bit(BitVector *bv, uint32_t i) { //setting to the bit vector
    if (i < bv->length) { //make sure i is in range
        bv->vector[i / 8] |= (0x1 << i % 8);
        return true;
    } else {
        return false;
    }
}

//clearing the ith bit in the vector
//if i is out of range, return false
//else return true to indicate the success
bool bv_clr_bit(BitVector *bv, uint32_t i) { //clearing the bit vector to 0
    if (i < bv->length) { //make sure i is in range
        bv->vector[i / 8] &= ~(0x1 << i % 8);
        return true;
    } else {
        return false;
    }
}

//return the ith bit in the bit vector,
//if it is out of range or the bit i is 0 return false
//else return true if the bit i is 1
bool bv_get_bit(BitVector *bv, uint32_t i) { //boolean logic getting the bit of 0 and 1
    if (i < bv->length) { //make sure i is in range
        return (bv->vector[i / 8] >> i % 8) & 0x1;
    }
    return false;
}

void bv_print(BitVector *bv); //debugging function (from previous assignment)
