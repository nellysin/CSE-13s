#include "defines.h"
#include "huffman.h"
#include "header.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "variables.h"

#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define OPTIONS "hvi:o:"

//CITE: Professor Long for steps of encode
//CITE: TA Eugene for pseudo code and structure of encode
//CITE: Tutor Eric for pseudo code of encode

void help(){ //printing out the menu
	printf("SYNOPSIS\n");
	printf("  A Huffman encoder.\n");
	printf("  Compresses a file using the Huffman coding algorithm.\n");
	printf("\n")
	printf("USAGE\n");
	printf("  ./encode [-h] [-i infile] [-o outfile]\n");
	printf("\n");
	printf("OPTIONS\n");
	printf("  -h		 Program usage and help.\n");
	printf("  -v		 Print compression statistics.\n");
	printf("  -i infile	 Input file to compress.\n");
	printf("  -o outfile	 Output of compressed data.\n");
	return;
}

//construct header

//print out the statistics


int main(int argc, char **argv){ 
	int infile = STDIN_FILENO;
	int outfile = STDOUT_FILENO;

	bool verbose = false;

	int opt = 0;

	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		switch(opt){
			case 'h': 
				help();
				exit(1);
			case 'v':
				verbose = true;
				break;
			case 'i':
			        infile = open(optarg, O_RDONLY);
				if(infile == -1){
					stderr = error message;
					exit(1);
				}
				break;
			case 'o':
				outfile = open(optarg, O_WRONGLY | O_CREAT | OTRUNE);
				if(outfile == -1){
					stderr = error message;
					exit(1);
				}
			default:
				break;
		}
	}			
	return 0;

	//histogram
	uint64_t histogram[ALPHABET] = {0};
	uint32_t symbols = 0;
	uint8_t buffer[BLOCK] = {0};
	histogram[0] += 1;
	histogram[ALPHABET] += 1;
	bytes_read = read_bytes(infile, buffer, BLOCK);
	while(bytes_read > 0){
		for(int i = 0; i < bytes_read; i += 1){
			if(histogram[buffer[i]] == 0){
				sum += 1;
			}
			histogram[buffer[i]] += 1;
		}
	}

	Node *root;
	root = build_tree(histogram);
	Code table[ALPHABET] = {0};
	build_codes(root, table);

	//construct header
	//file permissions
	
	struct stat statbuffer
	Header header;
	fstat(infile, statbuffer);
	fchmod(outfile, buffer.st_mode);

	header.magic = MAGIC;
	header.permissions = statbuffer.st_mode;
	header.tree_size = (3 * symbols) - 1;
	header.file_size = statbuffer.st_size;
	write_bytes(outfile, (uint8_t *)&h, sizeof(h));

	//dump tree
	dump_tree(outfile, root);

	//get the infile stats
	lseek(infile, 0, SEEK_SET);
	while(bytes_read > 0){
			for(int i = 0; i < bytes_read; i += 1){
				write_code(outfile, &table[buffer[i]]);
			}
	}
	flush_codes(outfile);
	if(verbose == true){
		//printing stats
	}

	delete_tree(&root);
	close(infile);
	close(outfile);
	return 0;
}
