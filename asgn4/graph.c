#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//CITE: Professor Long
//CITE: TA Eugene

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) { //from CITE: Prof. Long
    Graph *G = (Graph *) calloc(1, sizeof(Graph)); //intialize G, vertices, and undirected
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

void graph_delete(Graph **G) { //code from Prof. Long
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    //returns the number of vertices
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    // messes with the matrix (i = start, j = dst, k = weight (distance))
    if (G->undirected) {
        G->matrix[j][i] = k; //setting the graph if it is undirected
        G->matrix[i][j] = k; //goes both ways of j -> i and i -> j
        if (i < G->vertices && j < G->vertices) { //if i and j are within bounds
            return true;
        } else {
            return false;
        }
    } else {
        G->matrix[i][j] = k; // this is directed (only one way)
        if (i < G->vertices && j < G->vertices) { //check if vertices if within bounds:
            return true; //return true if it is and false otherwise
        } else {
            return false;
        }
    }
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (G->matrix[i][j] > 0) { //if there exists an edge from i to j
        if (i < G->vertices && j < G->vertices) { // if i & j are within bounds
            return true;
        } else {
            return false; //returning false if it isnt
        }
    } else {
        return false; //returning false if the weight is not greater than 0
    }
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    uint32_t k = G->matrix[i][j]; //to check if k is greater than 0 and i, j is within bounds
    if (i < G->vertices && j < G->vertices && k > 0) {
        return k; //returning k
    } else {
        return 0; //returning 0
    }
}

bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v] == 1) { //check if it is unvisited or not
        return true;
    } else {
        return false;
    }
}

void graph_mark_visited(Graph *G, uint32_t v) {
    G->visited[v] = true; //setting visited to true
    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    G->visited[v] = false; //setting unvisited to false
    return;
}
