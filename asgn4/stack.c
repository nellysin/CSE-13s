#include "graph.h"
#include "vertices.h"

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
	if (s){
		s-> top = 0; //intialize top to 0
		s-> capacity = capacity; //set to a specified capacity
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
		free((*s) -> items);
		free(*s);
		*s = NULL;
	}
	return;
}

bool stack_empty(Stack *s){
	if(s-> top == 0){
		return true;
	}else{
		return false;
	}
}

bool stack_full(Stack *s){
	if(s-> top == s-> capacity){
		return true;
	}else{
		return false;
	}
}

uint32_t stack_size(Stack *s){
	// how many elements are in there -- see top
	return s-> top;	
}

bool stack_push(Stack *s, uint32_t x){
	//returns the success of pushing *s to x
	if(s-> == s-> capacity){
		return false;
	}else{
		s-> items[s-> x]
		s-> top += 1;
		return true;
	}

}

bool stack_pop(Stack *s, uint32_t *x){
	//returns the success of popping *s to x
	if(s-> top == 0){
		return false;
	}else{
		*x = s-> items[s-> top];
		s-> top -= 1;
		return true;
	}
}

bool stack_peek(Stack *s, uint32_t *x){
	//similar to stack pop (returning the success) but it does not remove it from stack
	if(s-> top == 0){
		return false;
	}else{
		x* = s-> items[s-> top];
		return true;
	}
}

bool stack_copy(Stack *dst, Stack *src){
	//Taking the src and copy to the destination -- it keeps track of the paths
	//to find the shortest path
	if(dst == src){
		src-> items = (uint32_t *)calloc(s-> capacity, sizeof(uint32_t));
		dst-> items = (uint32_t *)calloc(s-> capacity, sizeof(uint32_t));
		if(!dst-> items){
			free(dst);
			free(src);
			src = NULL;
			dst = NULL;
		}
	}
}

void stack_print(Stack*s, FILE *outfile, char *cities[]){
	//prints the results of the stack and copy to a new file (outfile)
	for(uint32_t i = 0; i < s-> top; i += 1){
		printf(outfile, "%s", cities[s-> items[i]]);
		if(i + 1 != s-> top){
			printf(outfile, " -> ");
		}
	}
	printf(outfile, "\n");
}






