#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//CITE: Professor Long
//CITE: TA Eugene

struct Path {
	Stack *vertices;
	uint32_t length;
};

static uint32_t length;
Path *path_create(void){
	//set vertices as a freshly created stack (holding up to VERTICES)
	//initialize length to be 0
	vertices = Stack *stack_create(VERTICES);
	Path *p = (Path *)malloc(sizeof(vertices));
	(*p).vertices = vertices;
	(*p).length = 0; //initialize length to 0

}

void path_delete(Path **p){
        if(*p && (*p)-> vertices){
                free((*p)-> vertices);
                free(*p);
                *p = NULL;
        }
        return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G){
	//push vertex (v) onto the path p
	//length of path increases by weight
	//return true when successful
	*p = (*p).vertices[(*p).vertices] = v; 
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G){

}

uint32_t path_vertices(Path *p){
	return (*p).vertices;
}

uint32_t path_length(Path *p){
	return (*p).length;
}

void path_copy(Path *dst, Path *src){
	
}

void path_print(Path *p, FILE *outfile, char *cities[]){
	
}


