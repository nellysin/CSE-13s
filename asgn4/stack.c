#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//CITE: Professor Long
//CITE: TA Eugene

struct Stack {
	uint32_t top;
	uint32_t capacity;
	uint32_t *items;
};

Stack *stack_create(uint32_t capacity) {
	Stack *s = (Stack *) malloc(sizeof(Stack));
	if(s){
		s-> top = 0; //intialize top to 0
		s-> items = (uint32_t *) calloc(capacity, sizeof(uint32_t));//indicates the num of items to allocate memory
		if(!s-> items){
			free(s);
			s = NULL;
		}
	}
	return s;
}

void stack_delete(Stack **s){
	if(*s && (*s)-> items){
		free((*s)-> items);
		free(*s);
		*s = NULL;
	}
	return;
}

uint32_t stack_size(Stack *s){
        // how many elements are in there -- see top
        return (*s).top;
}

bool stack_empty(Stack *s){
	if( (*s).top == 0){
		return true;
	}else{
		return false;
	}
}

bool stack_full(Stack *s){
	if((*s).top == ((*s).capacity-1)){
		return false;
	}else{
		return true;
	}
}

bool stack_push(Stack *s, uint32_t x){
	//returns the success of pushing *s to x
	if((*s).top == ((*s).capacity-1)){
		return false;
	}else{
		(*s).items[(*s).top] = x;
		(*s).top += 1;
		return true;
	}

}

bool stack_pop(Stack *s, uint32_t *x){
	//returns the success of popping *s to x
	if((*s).top == 0){
		return false;
	}else{
		(*s).top -= 1;
		*x = (*s).items[(*s).top];
		return true;
	}
}

bool stack_peek(Stack *s, uint32_t *x){
	//similar to stack pop (returning the success) but it does not remove it from stack
	if((*s).top == 0){
		return false;
	}else{
		*x = (*s).items[((*s).top) -1];
		return true;
	}
}

void stack_copy(Stack *dst, Stack *src){
	//Taking the src and copy to the destination -- it keeps track of the paths
	//to find the shortest path
	//Stack *src = (Stack *) malloc(sizeof(Stack));
	for(uint32_t i = 0; i <= stack_size(src); i+= 1){
		dst->items[i] = src-> items[i];
		dst-> top = src-> top;
	}
	dst-> items = src-> items;
	//(*dst).top = (*src).top;
	return;

}

void stack_print(Stack*s, FILE *outfile, char *cities[]){
	//prints the results of the stack and copy to a new file (outfile)
	for(uint32_t i = 0; i < s-> top; i += 1){
		fprintf(outfile, "%s", cities[s-> items[i]]);
		if(i + 1 != s-> top){
			fprintf(outfile, " -> ");
		}
	}
	fprintf(outfile, "\n");
	return;
}
