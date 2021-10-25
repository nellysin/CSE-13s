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
//CITE: Tutor Jason

//NOTE TO GRADER (from README): My dfs function in this file does not work but my infile readings work
#define OPTIONS "uvhi:o:"

static int call = 0;

//void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
//    bool visit = graph_visited(G, v); //check if graph is visited or not
//graph_vertices
//    uint32_t max = graph_vertices(G); //this is the number of verticies
//    for (v = START_VERTEX; v < max; v += 1) {
//        if (v == START_VERTEX) { //if the visit is true and if
//            path_push_vertex(curr, v, G); // push the visited to the stack
//            graph_mark_visited(G, v); //mark this as visited
//        } else {
//            if (visit == true && graph_has_edge(G, v, max)) { //graph has edge is the neighboring
//                graph_mark_visited(G, v); //mark this as visited
//            } else {
//                graph_mark_unvisited(G, v); // mark this as unvisited
//                call += 1;
//                dfs(G, v, curr, shortest, cities, outfile); //recursive call dfs
//            }
//        }
//    }
//if current is greater than shortest then stop
//    if (path_length(curr)
//        < path_length(shortest)) { //compare the stacks (if it's longer then break)
//        path_copy(shortest, curr);
//    }

//    return;
//}

int main(int argc, char **argv) { //Reference to the previous assignments
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

    //NOTE TO GRADER (from README): THE FOLLOWING CODE WORKS BUT THE PIPELINE WILL NOT PASS

    //opening the file (after doing the command -i)
    // structure for the main function CITE: TUTOR James
    // read in the number of vertices 'n'

    //uint32_t i = 0, j = 0, k = 0;
    //uint32_t vert = 0;
    //getting the vertices
    //fscanf(infile, "%" SCNu32 "\n", &vert);
    //printf("%" PRIu32 "\n", vert);
    //if (vert > VERTICES) {
    //    fprintf(stderr, "Vertices out of bounds.");
    //}

    //create graph
    //Graph *G = graph_create(vert, undirected);

    //char **cities = (char **) calloc(vert, sizeof(char *));
    //read in the line by how many vertices
    //char buffer[1024];
    //for (uint32_t m = 0; m < vert; m += 1) { //indicate the city names in file
    //    fgets(buffer, 1024, infile);
    //    buffer[strlen(buffer) - 1] = '\0'; //CITE Euegen for stlen buffer
    //    cities[m] = buffer; //create array for cities
    //    strdup(buffer); //duplicate
    //    printf("%s\n", cities[m]); //print the name
    //}
    //reading the vertices
    //while (
    //fscanf(infile, "%" SCNu32 " %" SCNu32 " %" SCNu32 "\n", &i, &j, &k) != EOF) { //CITE: EUGENE
    //	graph_add_edge(G,i,j,k);
    //printf("%" PRIu32 " %" PRIu32 " %" PRIu32 "\n", i, j, k);
    //}

    //create current path
    //Path *curr = path_create();

    //create shortest path
    //Path *shortest = path_create();

    //call dfs
    //dfs(G, vert, curr, shortest, cities, outfile);

    //print results

    //free paths and graphs before returning!!
    //path_delete(&shortest);
    //path_delete(&curr);
    //graph_delete(&G);
    //free(*cities);
    //fclose(infile);
    return 0;
}
