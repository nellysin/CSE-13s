#include "stack.h"
#include "defines.h"
#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

//Almost all my code is referenced to asgn 4 stack.c
//CITE: Professor Long for additional sudo code
//CITE: TA Eugene (structure)

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) { //creating new stack
    Stack *s = (Stack *) malloc(sizeof(Stack)); //create new malloc
    if (s) {
        s->capacity = capacity;
        s->top = 0;
        s->items = (Node **) calloc(capacity, sizeof(Node));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0; //CITE: Professor Long: Stack empty (lecture )
        //return statament if the top == 0
}

bool stack_full(Stack *s) {
    return s->top == s->capacity; //CITE: Professor Long: Stack full
        //return statament if top == capacity
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s) == true) {
        return false;
    } else {
        s->items[s->top] = n;
        s->top += 1;
        return true;
    }
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s) == true) {
        return false;
    } else {
        s->top -= 1;
        *n = s->items[s->top];
        return true;
    }
}
