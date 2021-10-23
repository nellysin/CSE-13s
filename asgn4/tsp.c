#include "graph.h"
#include "path.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

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
	//??idk where to use the outfile and cities??
	v = START_VERTEX;
	Stack *s = stack_create(graph_vertices(G)); //create new stack

	while(!stack_empty(s)){ //while stack is not empty
		stack_pop(s, &v); //do stack pop
		visit = graph_visited(G, v);//check if graph is visited or not
	for(uint32_t u = 0; u < graph_vertices(G); u +=1){
		if(visit == 0 && graph_has_edge(G, v,)){ //??what would the graph has edge parameters be??
			stack_push(s, v) // push the visited to the stack 
			graph_mark_visited(G, v); //mark this as visited
		}else{
			dfs(G, v, curr, shortest, cities, outfile); //recursive call dfs
                        call += 1; //increment the number of recursive call
			graph_mark_unvisited(G,v); // mark this as unvisited
		}
	}
	stack_copy(shortest, curr);
	return;
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
			printf("Using %s as input file\n", optarg);
			infile = fopen(optarg, "r");
			break;
		case 'o':
			printf("Using %s as output file\n", optarg);
			outfile = fopen(optarg, "w");
			break;
		}
	}
	//opening the file 
	//??but file is unfound since it is not defined??
	FILE-> infile = fopen("example.graph", "r"); 

        //scan in number (reading in the number of vertices)
        uint32_t number = 0;
        fscanf(infile, "%" SCNu32 "\n", &number);

        //read a line
        char buf[1024];
        fgets(buf, 1024, infile);

        //read tuple 
        uint32_t a = 0, b = 0;
        fscanf(infile, "%" SCNu32 " %" SCNu32 "\n", &a, &b);

        printf("number = %" PRIu32 "\n", number);
        printf("line = %s", buf);
        printf("tuple = <%" PRIu32 ", %" PRIu32 ">\n", a, b);

        FILE *infile = stdin;
        FILE *outfile = stdout;

	char buf[1024];
	fgets(buf, 1024, infile);
	buf[strlen(buf) -1] = '\0'; // getting rid of newline
	fputs(buf, outfile);

	//create graph 'G'
	//reading the rest of the file and add each edge to graph 'G'
	//create current path 
	//create shortest path
	//calling DFS
	//printing results (verbose)

	return 0;
}
