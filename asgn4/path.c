#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//CITE: Professor Long
//CITE: TA Eugene
//CITE: Tutor Miles & Brian(Path debugging)

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    //set vertices as a freshly created stack (holding up to VERTICES)
    //initialize length to be 0
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0; //initialize length to 0

    return p;
}

void path_delete(Path **p) {
    free(*p);
    *p = NULL;
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    //push vertex (v) onto the path p
    //length of path increases by weight
    //return true when successful
    if (stack_full(p->vertices) == true) { // when stack_full is false
        return false;
    } else {
        //stack_push(p-> vertices, v); //pushing v to p.vertices
        uint32_t first = (v - 1); //for not overflowing the path
        stack_peek(p->vertices, &first); //access the weight
        stack_push(p->vertices, v); //pushing v to p.vertices
        uint32_t w = graph_edge_weight(G, first, v); //get the weight
        p->length += w; //use peek to access the weight of the stack
        return true;
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices) == true) { //when stack empty is false
        return false;
    } else {
        uint32_t start = *(v - 1); //for not overflowing the path
        stack_peek(p->vertices, &start); //to access the weight
        stack_pop(p->vertices, v); //popping v from p.vertices
        uint32_t w = graph_edge_weight(G, start, *v); //get the weight
        p->length -= w; //stack_peek(Stack *s, uint32_t *x)
        return true;
    }
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices); //returning number of vertices
}

uint32_t path_length(Path *p) {
    return p->length; //returning length
}

void path_copy(Path *dst, Path *src) {
    //copy(shortest path, current path)
    //same as stack copy, but also copies the length
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities); //printing path
    return;
}
