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
	Path *p = (Path *)malloc(sizeof(Path));
	(*p).vertices = stack_create(VERTICES)
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
	if(stack_full(*p) == 0){
		(*p).vertices[(*p).top] = v;
		(*p).length += graph_edge_weight(Graph *G, v, vertices[((*p).top)-1]);
		return true;
	}else{
		return false;
	}
	//how do we add weight?
	//b/c graph_edge_weight have 3 paramters: how do we get i and j to fill the parameters? 
	//how would v be pushed to the path if top isn't identified here?
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G){
	if(stack_empty(*p) == 0){
		(*p)vertices[(*p).top] = v;
		(*p).length -= graph_edge_weight(Graph *G, v, vertices[((*p).top)-1]); //stack_peek(Stack *s, uint32_t *x)
		return true;
	}else{
		return false;
	}
}

uint32_t path_vertices(Path *p){
	return (*p).vertices;
}

uint32_t path_length(Path *p){
	return (*p).length;
}

void path_copy(Path *dst, Path *src){

	//copy(shortest path, current path)
	//wouldn't this be the same as stack copy?
	for(uint32_t i = 0; i < (*p).vertices; i += 1){
		(*dst).vertices[((*dst).top)] = (*p).vertices[(*p).top];
	}
	/*        for(uint32_t i = 0; i < (*s).top; i+= 1){
                (*src).items[((*src).top)] = (*s).items[(*s).top]
                        for(uint32_t j = 0; j < (*src).top; j += 1){
                                (*dst).items[(*src).top] = (*src).items[((*src).top)];
                        }
        }
        return;

}*/

}

void path_print(Path *p, FILE *outfile, char *cities[]){
	fprintf(stack_print(*p, *outfile, *cities[]));
}
