#include "defines.h"
#include "huffman.h"
#include "header.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>

#define OPTIONS "hvi:o:"

void help(void){ //printing out the menu
        printf("SYNOPSIS\n");
        printf("  A Huffman decoder.\n");
        printf("  decompresses a file using the Huffman coding algorithm.\n");
        printf("\n");
        printf("USAGE\n");
        printf("  ./decode [-h] [-i infile] [-o outfile]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -h             Program usage and help.\n");
        printf("  -v             Print compression statistics.\n");
        printf("  -i infile      Input file to decompress.\n");
        printf("  -o outfile     Output of decompressed data.\n");
        return;
}

int main(int argc, char **argv){
        int infile = STDIN_FILENO;
        int outfile = STDOUT_FILENO;
        if(outfile != STDOUT_FILENO){
                close(outfile);
        }
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
                                infile = open(optarg, O_RDONLY| O_CREAT);
                                if(infile == -1){
                                        fprintf(stderr, "Error: open infile failed.\n");
                                        exit(1);
                                }
                                break;
                        case 'o':
                                outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
                                if(outfile == -1){
                                        fprintf(stderr, "Error: Unable to write file.\n");
                                        exit(1);
                                }
                                break;
                        default:
                                help();
                                exit(1);
                }
        }

	//file permissions
	Header h = {0,0,0,0};
	
	read_bytes(infile, (uint8_t *)&h, sizeof(h));
	if(h.magic != MAGIC){
		fprintf(stderr, "Bad magic");
		close(infile);
		close(outfile);
		return 0;
	}
	fchmod(outfile, h.permissions);

	return 0;
}

