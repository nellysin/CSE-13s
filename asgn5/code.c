#include "defines.h"
#include "code.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// CITE: Professor Long for sudo code
// CITE: TA Eugene for code init 

Code code_init(void){
	Code *c = NULL;	//create new code on the stack
	c-> top = 0;	// set top to 0
	for(int i = 0; i < MAX_CODE_SIZE; i += 1){ //zeroing out the array of bits
		c->bits[i] = 0;
	}
	return *c;
}

uint32_t code_size(Code *c){
	return c->top;
}

bool code_empty(Code *c){
	return c->top == 0;
}

bool code_full(Code *c){
	return c->top == MAX_CODE_SIZE;
}

//bool code_set_bit(Code *c, uint32_t i){
//}
