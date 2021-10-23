#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

//CITE: Professor Long for dfs
//CITE: TA Eugene for structure

#define OPTIONS "uvhi:o:"

static int call = 0;
//static FILE* infile = stdin;
//static FILE* outfile = stdout;

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile){
	//label v as visited
	//for all edges from v to w in G.adjacentEdges(v) do
	//if vertex w is not labeled as visited then
	//recursively call DFS(G,w)
	//label v as unvisted
	v = START_VERTEX;
	uint32_t vertex = graph_vertices(G);
	shortest = path_create(); // shortest path
	curr = path_create(); //current path
	bool visit = graph_visited(G, v);//check if graph is visited or not
	for(uint32_t u = 0; u < vertex; u +=1){
		if(visit == true && graph_has_edge(G, v, vertex)){ //??what would the graph has edge parameters be??
			path_push_vertex(curr, v, G); // push the visited to the stack 
			graph_mark_visited(G, v); //mark this as visited
		}else{
			graph_mark_unvisited(G,v); // mark this as unvisited
			call += 1; //increment the number of recursive call
        		dfs(G, v, curr, shortest, cities, outfile); //recursive call dfs
		}
		}
	//if current is greater than shortest then stop
        if(path_length(curr) > path_length(shortest)){  //compare the stacks (if it's longer then break)
                path_copy(shortest, curr);
                return;
        }
}

int main(int argc, char **argv){
	call = 0;
	int opt = 0;
	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		switch (opt){
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
			printf("enables verbose printing prints out ALL hamiltonian paths & number of recursive calls");
			//call function that prints all
			break;
		case 'u': 
			printf("specifies the graph to be undirected");
			//setting to be undirected (function)
			break;
		case 'i':
			printf("Using ... as input file\n");
			//inputfile_name = optarg;
			break;
		case 'o':
			printf("Using ... as output file\n");
			//outfile = fopen(optarg, "w");
			break;
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
			break;
		}
	}

char **cities(char n){
	char **m = (char **)calloc(n, sizeof(char *));
	assert(m);

	for (int i = 0; i< n; i +=1){
		m[i] = (int *)calloc(n, sizeof(char));
		assert(m[i]);
	}

	return m;
}

void cities delete(char **m, int n){
	for(int i = 0; i < n; i += 1){
		free(m[i]);
		m[i] = NULL;
	}

	free(m);
	m = NULL;
	return;
}

	//FILE* infile = stdin;
	//opening the file 
        FILE* infile = fopen("mythical.graph", "r");
	//FILE* outfile = stdout;

	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t k = 0;

	uint32_t numvert = 0;
	if(1 != sscanf(buffer, "%u", &numvert)){
		printf("error");
	}else{
		printf("number = %" PRIu32 "\n", numvert);
	}

	char **cities = 
	for(uint32_t i = 0; i < numvert; i += 1){


	for(uint32_t i = 0; i < numvert; i += 1){
		fgets(buffer, 1024, infile);
	}

	while(NULL != fgets(buffer, 1024, infile)){
		sscanf(buffer, "%u %u %u", &i, &j, &k);
		printf("tuple = <%" PRIu32 ", %" PRIu32 ", %" PRIu32 ">\n", i, j, k);
	}
        //scan in number (reading in the number of vertices)
/*        uint32_t numvert = 0;
        fscanf(infile, "%" SCNu32 "\n", &numvert);

        //read a line (reading the city names)
        uint32_t i = 0;
	uint32_t j = 0;
	uint32_t k = 0;

	char **cities = NULL;
        fgets(*cities, numvert, infile);
	*cities[strlen(*cities) -1] = '\0';

	//create graph "G"
//	Graph *G = graph_create(numvert, undirected);

        //read tuple 
        char i = '\0';
        char j = '\0';
	char k = '\0';
	char city_number;

	sscanf(&i, &j, &k);
	
	fgets(&city_number, numvert, infile);

        printf("number = %" PRIu32 "\n", numvert);
        printf("line = %s", *cities);*/
        //printf("tuple = <%" PRIu32 ", %" PRIu32 ", %" PRIu32 ">\n", i, j, k);
	//create graph 'G'
	//reading the rest of the file and add each edge to graph 'G'
	//create current path 
	//create shortest path
	//calling DFS
	//printing results (verbose)

	return 0;
}
