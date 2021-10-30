#include "defines.h"
#include "code.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// CITE: Professor Long for sudo code
// CITE: TA Eugene for code init 

Code code_init(void){
	Code *c = NULL;	//create new code on the stack
	c-> top = 0;	// set top to 0
	for(int i = 0; i < MAX_CODE_SIZE; i += 1){ //zeroing out the array of bits
		c->bits[i] = 0;		//setting the bits[i] == 0
	}
	return *c;
}

uint32_t code_size(Code *c){
	return c->top; //returning the size of the code (top)
}

bool code_empty(Code *c){
	if(c->top == 0){ //if code is empty then return true
		return true;
	}
	else{
		return false; //else return false
	}
}

bool code_full(Code *c){
	if(c->top == ALPHABET){ //if code is full return true
		return true;
	}
	else{
		return false; //else return false
	}
}

bool code_set_bit(Code *c, uint32_t i){
	if(i > ALPHABET){	//if i is out of bounds
		return false;  //return false
	}
	else{
		c->bits[i / MAX_CODE_SIZE] |= (0x1 << i % MAX_CODE_SIZE);//CITE: Professor Long for the setbit from bv8
		return true; //we are setting the bits
	}
}

bool code_clr_bit(Code *c, uint32_t i){
	if(i > ALPHABET){ //if i is out of bounds
		return false; //return false
	}
	else{
		c->bits[i / MAX_CODE_SIZE] &= ~(0x1 << i % MAX_CODE_SIZE); //CITE: Professor Long from comments repo
		return true; //we are clearing the bits by using &
	}
}

bool code_get_bit(Code *c, uint32_t i){
	if(i > ALPHABET || i == 0){ //if i is out of bounds and it's 0 then return false
		return false;
	}else{
		if(i == 1){ //if and only if i = 1 
			i = (c->bits[i/MAX_CODE_SIZE] >> i % MAX_CODE_SIZE) & 0x1; //CITE: Professor Long from comments repo
			return true;	//we are getting the bit and setting it to i
		}else{
			return false; // double if i != 1 return false
		}
	}
}

bool code_push_bit(Code *c, uint8_t bit){ //this is similar to stack.c
	if(code_full(c) == true){ //if code is not full yet, then keep pushing + incrementing the top
		return false;
	}else{
		c->bits[c->top] = bit;
		c->top += 1;
		return true;
	}
}

bool code_pop_bit(Code *c, uint8_t *bit){ //similar to stack.c
	if(code_empty(c) == true){ //if the code is not empty yet, then continue popping and decrement the top
		return false;
	}else{
		c->top -= 1;
		*bit = c->bits[c->top];
		return true;
	}
}

void code_print(Code *c){
	code_push_bit(c, 1);
	code_push_bit(c, 0);
	code_push_bit(c, 1);
	code_push_bit(c, 0);
	for(int i = 0; i < 4; i+= 1){
		printf("%d \n", bits[i]);
	}
	return;
}

int main(void){
	Code c = code_init();
	code_print(&c);
	return 0;
}
