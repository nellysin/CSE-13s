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

//CITE: Professor Long
//CITE: TA Eugene

#define OPTIONS "uvhi:o:"

static int call = 0;
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile){
	//label v as visited
	//for all edges from v to w in G.adjacentEdges(v) do
	//if vertex w is not labeled as visited then
	//recursively call DFS(G,w)
	//label v as unvisted
	v = START_VERTEX;
	verticies = path_verticies(G)
	Stack *s = path_create(verticies); //create new stack
	//if current is greater than shortest then stop 
	if(path_length(curr) > path_length(shortest)){  //compare the stacks (if it's longer then break)
		path_copy(shortest, curr);
		return;						
	}
	while(!path_empty(vertices)){ //while visited path is not full
		path_pop_vertex(s, &v); //push
		if(v == START_VERTEX){
			graph_mark_unvisited(G,v);
		}
		bool visit = graph_visited(G, v);//check if graph is visited or not
		uint32_t w = graph_vertices(G);
	for(uint32_t u = 0; u < w; u +=1){
		if(visit == true && graph_has_edge(G, v,w)){ //??what would the graph has edge parameters be??
			path_push_vertex(s, v); // push the visited to the stack 
			graph_mark_visited(G, v); //mark this as visited
		}else{
			graph_mark_unvisited(G,v); // mark this as unvisited
		}
		}
	}
	call += 1; //increment the number of recursive call
	dfs(G, v, curr, shortest, cities, outfile); //recursive call dfs
}

int main(int argc, char **argv){
	call = 0;
	int opt = 0;
	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		switch (opt){
		case 'h':
			printf("SYNOPSIS\n");
			printf("  Traveling Salesman Problem using DFS\n");
			printf("\nUSAGE");
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
			//infile = fopen(optarg, "r");
			break;
		case 'o':
			printf("Using ... as output file\n");
			//outfile = fopen(optarg, "w");
			break;
		}
	}

	//opening the file 
       	FILE *infile = fopen("mythical.graph", "r");
        FILE *infile = stdin;
	FILE *outfile = stdout;	

        //scan in number (reading in the number of vertices)
        uint32_t numvert = 0;
        fscanf(infile, "%" SCNu32 "\n", &numvert);
	if(numvert > VERTICES){
		printf("Error");
	}

        //read a line (reading the city names)
        char read_city[numvert];
        fgets(read_city, numvert, infile);
	read_city[strlen(read_city) -1] = '\0';
	for(uint32_t i; i < numvert; i += 1;){
		if(strdup(read_city[i]) 


	//create graph "G"
	graph_create(numvert, )

        //read tuple 
        uint32_t a = 0, b = 0;
        fscanf(infile, "%" SCNu32 " %" SCNu32 "\n", &a, &b);

        printf("number = %" PRIu32 "\n", number);
        printf("line = %s", buf);
        printf("tuple = <%" PRIu32 ", %" PRIu32 ">\n", a, b);

	char read_city[numvert];
	fgets(read_city, numvert, infile);
	read_city[strlen(buf) -1] = '\0'; // getting rid of newline
	fputs(read_city, outfile);

	//create graph 'G'
	//reading the rest of the file and add each edge to graph 'G'
	//create current path 
	//create shortest path
	//calling DFS
	//printing results (verbose)
	
	return 0;
}
