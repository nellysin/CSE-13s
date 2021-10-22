#include <graph.h>
#include <path.h>
#include <stack.h>

#include <stdio.h>
#include <intypes.h>
#include <unistd.h>
#include <string.h>

//CITE: Professor Long
//CITE: TA Eugene

void DFS(Graph *G, uint32_t v){
	//label v as visited
	//for all edges from v to w in G.adjacentEdges(v) do
	//if vertex w is not labeled as visited then
	//recursively call DFS(G,w)
	//label v as unvisted
	Set visited = set_empty();
	Stack *s = stack_create(graph_vertices(g));
	stack push(s, v);

	while(!stack_empty(s)){
		stack_pop(s, &v);
		visited = set_insert(visited,v );

		for(uint32_t u = 0; u < graph_vertices(g); u += 1){
			if(!set_member(visited u) && graph_has_edge(g,v,u)){
				stack_push(s,u);
			}
		}
	}
}

int main(int argc, char **argv){
	/*FILE-> infile = fopen("example.graph", "r");

	//scan in number
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

	return 0;

	FILE *infile = stdin;
	FILE *outfile = stdout;*/

	int opt = 0;
	while((opt = getopt(argc, argv, "i:o")) != -1){
		switch (opt){
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
	FILE-> infile = fopen("example.graph", "r");

        //scan in number
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

        return 0;

        FILE *infile = stdin;
        FILE *outfile = stdout;

	char buf[1024];
	fgets(buf, 1024, infile);
	buf[strlen(buf) -1] = '\0'; // getting rid of newline
	fputs(buf, outfile);

	return 0;
}
