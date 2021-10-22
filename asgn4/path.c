#include "path.h"
#include "stack.h"
#include "vertices.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

//CITE: Professor Long
//CITE: TA Eugene

static uint32_t length;

struct Path {
	Stack *vertices;
	uint32_t length;
};

static uint32_t length;
Path *path_create(void){
	//set vertices as a freshly created stack (holding up to VERTICES)
	//initialize length to be 0
	Path *p = (Path *)malloc(sizeof(Path));
	(*p).vertices = stack_create(VERTICES);
	(*p).length = 0; //initialize length to 0

	return p;
}

void path_delete(Path **p){
        free(*p);
        *p = NULL;
        return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G){
	//push vertex (v) onto the path p
	//length of path increases by weight
	//return true when successful
	//questions:
	//b/c we need to call stack_full
	//what are the parameters for stack_full? -- would if be just *p?
	if(stack_full((*p).vertices) == 0){
		uint32_t peekpush = stack_peek((*p).vertices,&v);
		stack_push((*p).vertices, v);
		(*p).length += graph_edge_weight(G, v, peekpush); //use peek to access the weight of the stack 
		return true;
	}else{
		return false;
	}
	//how do we add weight?
	//b/c graph_edge_weight have 3 paramters: how do we get i and j to fill the parameters? 
	//how would v be pushed to the path if top isn't identified here?
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G){
	if(stack_empty((*p).vertices) == 0){
		uint32_t peekpop = stack_peek((*p).vertices, v);
		stack_pop((*p).vertices, v);
		(*p).length -= graph_edge_weight(G, *v, peekpop); //stack_peek(Stack *s, uint32_t *x)
		return true;
	}else{
		return false;
	}
}

uint32_t path_vertices(Path *p){
	return stack_size((*p).vertices);
}

uint32_t path_length(Path *p){
	return (*p).length;
}

void path_copy(Path *dst, Path *src){
	//copy(shortest path, current path)
	//same as stack copy
	stack_copy((*dst).vertices, (*src).vertices);
        return;
	
}

void path_print(Path *p, FILE *outfile, char *cities[]){
	for(uint32_t i = 0; i < path_vertices(p); i += 1){
                fprintf(outfile, "%s", cities[(*p).vertices[i]]);
                if(i + 1 != path_vertices(p)){
                        fprintf(outfile, " -> ");
                }
        }
        fprintf(outfile, "\n");
}


