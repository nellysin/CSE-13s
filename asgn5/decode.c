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
	Header header = {0,0,0,0};	

	read_bytes(infile, (uint8_t *)&header, sizeof(header)); //read file
	if(header.magic != MAGIC){		//if permissions magic reaches to MAGIC
		fprintf(stderr, "Bad magic"); //print the error message
		close(infile);		//close file
		close(outfile); 	//close outfile
	}
	uint8_t tree[header.tree_size];
	fchmod(outfile, header.permissions);
	read_bytes(infile, tree, header.tree_size);

	Node *root = rebuild_tree(header.tree_size, tree);

//	uint64_t i = 0;
//        uint8_t buf[BLOCK];
	/*Node *tem;

        while(i < header.file_size){
                uint8_t bit;
                if(tem->left == NULL && tem->right == NULL){
                        buf[i % BLOCK] = tem->symbol;
                        tem = root;
                        i+= 1;
                        if (i == BLOCK){
                                write_bytes(outfile, buf, sizeof(buf));
                        }
                }
                read_bit(infile, &bit);
                if(bit == 0){
                        tem = tem->left;
                }
                if(bit == 1){
                        tem = tem->right;
                }
        }
        if(i != BLOCK && i != 0){
                write_bytes(outfile, buf, (i % BLOCK));
        }*/
        delete_tree(&root);
	close(infile);
	close(outfile);
	return 0;
}

