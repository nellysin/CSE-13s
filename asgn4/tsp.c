#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//CITE: Professor Long for dfs sudo
//CITE: TA Eugene for structure

#define OPTIONS "uvhi:o:"

static int call = 0;
//static FILE* infile = stdin;
//static FILE* outfile = stdout;

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    //if the city is reachable and it is not visited:
    //	label v as visited
    //if the city is not reachable:
    //	label v as unvisited.
    //for all edges from v to w in G.adjacentEdges(v) do
    //if vertex w is not labeled as visited then
    //recursively call DFS(G,w)
    v = START_VERTEX;
    uint32_t vertex = graph_vertices(G);
    shortest = path_create(); // shortest path
    curr = path_create(); //current path
    bool visit = graph_visited(G, v); //check if graph is visited or not
    for (uint32_t u = 0; u < vertex; u += 1) {
        if (visit == true
            && graph_has_edge(G, v, vertex)) { //??what would the graph has edge parameters be??
            path_push_vertex(curr, v, G); // push the visited to the stack
            graph_mark_visited(G, v); //mark this as visited
        } else {
            graph_mark_unvisited(G, v); // mark this as unvisited
            call += 1; //increment the number of recursive call
            dfs(G, v, curr, shortest, cities, outfile); //recursive call dfs
        }
    }
    //if current is greater than shortest then stop
    if (path_length(curr)
        > path_length(shortest)) { //compare the stacks (if it's longer then break)
        path_copy(shortest, curr);
        return;
    }
}

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    call = 0;
    int opt = 0;
    bool undirected;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n");
            printf("  Traveling Salesman Problem using DFS\n");
            printf("\nUSAGE\n");
            printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
            printf("\nOPTIONS\n");
            printf("  -u		Use undirected graph.\n");
            printf("  -v		Enable verbose printing.\n");
            printf("  -h		Program usage and help.\n");
            printf("  -i infile	Input containing graph (default: stdin)\n");
            printf("  -o outfile	Output of computed path (default: stdout)\n");
        case 'v':
            printf("enables verbose printing prints out ALL hamiltonian paths & number of "
                   "recursive calls");
            //call function that prints all
            break;
        case 'u':
            printf("specifies the graph to be undirected");
            //setting to be undirected
            undirected = true;
            break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        default:
            printf("SYNOPSIS\n");
            printf("  Traveling Salesman Problem using DFS\n");
            printf("\nUSAGE\n");
            printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
            printf("\nOPTIONS\n");
            printf("  -u            Use undirected graph.\n");
            printf("  -v            Enable verbose printing.\n");
            printf("  -h            Program usage and help.\n");
            printf("  -i infile     Input containing graph (default: stdin)\n");
            printf("  -o outfile    Output of computed path (default: stdout)\n");
            exit(1);
        }
    }
    //This part has not yet been finished but these were my ideas:
    //opening the file (after doing the command -i) -- structure CITE: TUTOR James
    // read in the number of vertices 'n'
    char buffer[1024]; //CITE: TA Eugene
    uint32_t i = 0, j = 0, k = 0;
    uint32_t n = 0;

    fscanf(infile, "%" SCNu32 "\n", &n);
    printf("%" PRIu32 "\n", n);

    //read in the line by how many vertices
    for (uint32_t t = 0; t < n; t += 1) {
        fgets(buffer, 1024, infile);
        printf("%s", buffer);
        //maybe create an array special to cities
    }
    //create graph 'G'

    //add edge to graph 'G' and reading edges
    while (fscanf(infile, "%" SCNu32 " %" SCNu32 " %" SCNu32 "\n", &i, &j, &k) != EOF) {
        fscanf(infile, "%" SCNu32 " %" SCNu32 " %" SCNu32 "\n", &i, &j, &k);
        printf("%" PRIu32 " %" PRIu32 " %" PRIu32 "\n", i, j, k);
        //call graph edge to assign i, j, and k in the graph
    }
    //create current path

    //create shortest path
    //call dfs

    //print results

    //free paths and graphs before returning!!
    return 0;
}
