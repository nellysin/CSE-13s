#include <stdio.h>
#include <intypes.h>

//CITE: Professor Long
//CITE: TA Eugene

int main(int argc, char **argv){
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
}
