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
};

Graph *graph_create(uint32_t vertices, bool undirected){
	Graph *G = (Graph *)calloc(1, sizeof(Graph));
	G-> vertices = vertices;
	G-> undirected = undirected;
	return G;
}

void graph_delete(Graph **G){
	free(*G);
	*G = NULL;
	return;
}

uint32_t graph_vertices(Graph *G){
	//returns the number of vertices
	return G-> vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k){
	// messes with the matrix (i = start, j = dst, k = weight (distance))
	if(G-> undirected){
		G-> matrix[j][i] = k;
		G-> matrix[i][j] = k;
		if(i < G-> vertices && j < G-> vertices){
			return true;
		}else{
			return false;
		}
	}else{
		G-> matrix[i][j] = k;
		if(i < G-> vertices && j < G-> vertices){
			return true;
		}else{
			return false;
		}
	}

}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j){
	if(i <= G-> vertices && j= < G-> vertices){
	       return true;
	}else{
		return false;
	}	
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j){
        uint32_t k = G-> matrix[i][j];
	if(i < G-> vertices || j < G-> vertices){
                return k;
        }else{
                return 0;
        }
}

bool graph_visited(Graph *G, uint32_t v){
	if(G-> visited[v] == 1){
		return true;
	}else{
		return false;
	}
}

void graph_mark_visited(Graph *G, uint32_t v){
	G-> visited[v] = true;
	return;
}

void graph_mark_unvisited(Graph *G, uint32_t v){
	G-> visited[v] = false;
	return;
}

/*void graph_print(Graph *G){
	for(uint32_t i = 0; i < G-> vertices; i += 1){
		for(uint32_t j = 0; j < G-> vertices; j += 1){
			printf("%u", G-> matrix[i][j]);
			printf("\n");
		}
	}
}*/
