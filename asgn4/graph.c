#include "graph.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//CITE: Professor Long
//CITE: TA Eugene

struct Graph {
	uint32_t vertices;
	bool undirected;
	bool visited [VERTICES];
	uint32_t matrix [VERTICES][VERTICES];
	uint32_t i;
	uint32_t j;
	uint32_t k;
};

Graph *graph_create(uint32_t vertices, bool undirected){
	Graph *G = (Graph *)calloc(1, sizeof(Graph));
	G-> vertices = vertices;
	G-> undirected = undirected;
	G-> matrix[i][j] = k;
	return G;
}

void graph_delete(Graph **G){
	free(*G);
	*G = NULL;
	return;
}

uint32_t graph_vertices(Graph *G){
	for(uint32_t vertices = 0; vertices < VERTICES; vertices += 1){
		G[vertices];
	}
	return vertices
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k){
	if(undirected){
		i-> j;
		j-> i;
		k;
	}
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j){
}

bool graph_visited(Graph *G, uint_t v){
}

void graph_mark_visited(Graph *G, uint32_t v){
}

void graph_mark_unvisited(Graph *G, uint32_t v){
}

void graph_print(Graph *G){

}


