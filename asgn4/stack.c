#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//CITE: Professor Long for the sudo code
//CITE: TA Eugene

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

Stack *stack_create(uint32_t capacity) { //CITE: Prof. Long
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->capacity = capacity; //initialize capacity
        s->top = 0; //intialize top to 0
        s->items = (uint32_t *) calloc(
            capacity, sizeof(uint32_t)); //indicates the num of items to allocate memory
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) { //CITE: Prof. Long for the freeing of stack
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

uint32_t stack_size(Stack *s) {
    // how many elements are in there -- see top
    return s->top;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) { //check stack is empty by if top points to 0
        return true;
    } else {
        return false;
    }
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) { //checking stack is full by if the top pointing to capacity
        return true;
    } else {
        return false;
    }
}

bool stack_push(Stack *s, uint32_t x) {
    //returns the success of pushing *s to x
    if (stack_full(s) == true) {
        return false;
    } else {
        s->items[s->top] = x;
        s->top += 1;
        return true;
    }
}

bool stack_pop(Stack *s, uint32_t *x) {
    //returns the success of popping *s to x
    if (stack_empty(s) == true) {
        return false;
    } else {
        s->top -= 1;
        *x = s->items[s->top];
        return true;
    }
}

bool stack_peek(Stack *s, uint32_t *x) {
    //similar to stack pop (returning the success) but it does not remove it from stack
    if (stack_empty(s) == true) {
        return false;
    } else {
        *x = s->items[(s->top) - 1];
        return true;
    }
}

void stack_copy(Stack *dst, Stack *src) {
    //Taking the src and copy to the destination -- it keeps track of the paths
    //to find the shortest path
    //Stack *src = (Stack *) malloc(sizeof(Stack));
    for (uint32_t i = 0; i < stack_size(src); i += 1) {
        dst->items[i] = src->items[i];
        dst->top = src->top;
    }
    return;
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    //prints the results of the stack and copy to a new file (outfile)
    for (uint32_t i = 0; i < s->top; i += 1) { //use for loop to iterate each item in the stack
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
    return;
}
