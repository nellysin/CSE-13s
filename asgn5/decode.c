#include "defines.h"
#include "huffman.h"
#include "header.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "code.h"

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

void help(void) { //printing out the menu
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

//CITE: Professor Long for steps of decode in assignment doc (ALL)
//CITE: TA Eugene for pseudo code and structure of decode (ALL) during 11/4 & 11/2 section
//CITE: Tutor Eric for pseudo code of decode during 11/3 (ALL) session

int main(int argc, char **argv) {
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    if (outfile != STDOUT_FILENO) {
        close(outfile);
    }
    bool verbose = false;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help(); exit(1);
        case 'v': verbose = true; break;
        case 'i':
            infile = open(optarg, O_RDONLY | O_CREAT);
            if (infile == -1) {
                fprintf(stderr, "Error: open infile failed.\n");
                exit(1);
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            if (outfile == -1) {
                fprintf(stderr, "Error: Unable to write file.\n");
                exit(1);
            }
            break;
        default: help(); exit(1);
        }
    }
    //file permissions
    Header header = { 0, 0, 0, 0 }; //CITE: TUTOR Eric -- initialize header

    read_bytes(infile, (uint8_t *) &header, sizeof(header)); //read file

    if (header.magic != MAGIC) { //if permissions magic reaches to MAGIC, verify the magic number
        fprintf(stderr, "Bad magic"); //print the error message
        close(infile); //close file
        close(outfile); //close outfile
        return 0;
    }
    uint8_t tree[header.tree_size]; //construct an array with the tree size
    fchmod(outfile, header.permissions); //file permissions
    read_bytes(infile, tree, header.tree_size); //reading the tree

    Node *root
        = rebuild_tree(header.tree_size, tree); //rebuild the tree - reconstruct the tree (asgn doc)

    Node *n = root; // this will be our current node
    uint64_t i = 0; //this is our index
    uint8_t buf[BLOCK]; //buffer with 256
    n = root; //current node

    while (i < header.file_size) { //while loop CITE: Tutor Jason for the while loop idea
        uint8_t bit; //check if bit is 1 or 0
        read_bit(infile, &bit); //read each bit (called)
        if (bit == 0 && n->left != NULL) { //check the left interior node when bit is 0
            n = n->left; //assign n to the left node
        }
        if (bit == 1 && n->right != NULL) { //check the right interior node when bit is 1
            n = n->right; //assign n to the right node
        }
        if (n->left == NULL && n->right == NULL) { //checking the leaf node first
            buf[i % BLOCK] = n->symbol; //buffer the symbol
            n = root; //n will start back to the root
            i += 1; //increment the index
            if (i == BLOCK && i != 0) { //if the buffer is filled
                write_bytes(outfile, buf, sizeof(buf)); //write out the bytes (called)
            }
        }
    }
    //CITE: Tutor Jason for reading rest of the tip
    if (i % BLOCK != 0 && i != 0) { //checking the rest of the bytes
        write_bytes(outfile, buf, (i % BLOCK)); //write out the rest of the bytes
    }

    //if verbose is true (print stats)
    /*if(verbose == true){
		double space = 0;
		fprintf(stderr, "Compressed file size:")*/

    delete_tree(&root); //MUST DELETE AND CLOSE FILES
    close(infile);
    close(outfile);
    return 0;
}
