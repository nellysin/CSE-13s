#include "defines.h"
#include "code.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//Most of what I have written is a reference to my stack.c --> which references to my asgn4
// CITE: Professor Long for most of the code sudo
// CITE: TA Eugene for code init for most of the code sudo, this is during 10/19 Section

Code code_init(void) {
    Code c; //create new code on the stack
    c.top = 0; // set top to 0
    for (int i = 0; i < MAX_CODE_SIZE; i += 1) { //zeroing out the array of bits
        c.bits[i] = 0; //setting the bits[i] == 0
    }
    return c;
}

uint32_t code_size(Code *c) {
    return c->top; //returning the size of the code (top)
}

bool code_empty(Code *c) {
    if (c->top == 0) { //if code is empty then return true
        return true;
    } else {
        return false; //else return false
    }
}

bool code_full(Code *c) {
    //c->top == ALPHABET
    if (c->top == ALPHABET) { //if code is full return true
        return true;
    } else {
        return false; //else return false
    }
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i > ALPHABET) { //if i is out of bounds
        return false; //return false
    } else {
        //[i/MAX_CODE_SIZE]
        c->bits[c->top / 8] |= (i << c->top % 8); //CITE: Professor Long for the setbit from bv8
        return true; //we are setting the bits
    }
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i > ALPHABET) { //if i is out of bounds
        return false; //return false
    } else {
        c->bits[c->top / 8] &= ~(i << c->top % 8); //CITE: Professor Long from comments repo
        return true; //we are clearing the bits by using &
    }
}

bool code_get_bit(Code *c, uint32_t i) {
    if (i > ALPHABET
                - 1) { //if i is out of bounds and it's 0 then return false & if and only if i = 1
        return false;
    }
    return (c->bits[c->top / 8] >> c->top % 8) & 0x1; //CITE: Professor Long from comments repo bv32
}

bool code_push_bit(Code *c, uint8_t bit) { //this is similar to stack.c (CITE: Eugene) 11/2 section
    if (code_full(c) == true) { //if code is not full yet, then keep pushing + incrementing the top
        return false;
    } else {
        if (bit == 1) {
            code_set_bit(c, bit); //set the bit if the bit is 1
            c->top += 1; //increment like a reg pushing
        } else {
            code_clr_bit(c, bit); //else clear the bit
            c->top += 1; //incremenet like a reg pushing
        }
        return true;
    }
}

bool code_pop_bit(Code *c, uint8_t *bit) { //similar to stack.c (CITE: Eugene) during 11/2 section
    if (code_empty(c)
        == true) { //if the code is not empty yet, then continue popping and decrement the top
        return false;
    } else {
        c->top -= 1; //decrement like a reg popping
        *bit = code_get_bit(c, c->top); //get the bit
        code_clr_bit(c, c->top); //and clearing the bit after
        return true;
    }
}

/*void code_print(Code *c) {
    for (uint i = 0; i < c->top; i += 1) {
        printf("%d", (0x1 & (c->bits[i / 8] >> (i % 8))));
        printf("\n");
    }
    return;
}*/
