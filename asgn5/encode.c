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

#define OPTIONS "hvi:o:"

//CITE: Professor Long for steps of encode in assignment doc (ALL)
//CITE: TA Eugene for pseudo code and structure of encode (ALL) during 11/4 & 11/2 section
//CITE: Tutor Eric for pseudo code of encode during 11/3 (ALL) session

/*uint32_t s_symbols = 0;
struct stat sbuffer;
//a constructor for the header
Header construct_header(int infile, int outfile) {
    Header header = {0,0,0,0};
    fstat(infile, &sbuffer);
    fchmod(outfile, sbuffer.st_mode);
    header.magic = MAGIC;
    header.permissions = sbuffer.st_mode;
    header.tree_size = (3 * s_symbols) - 1;
    header.file_size = sbuffer.st_size;
    return header;
}*/

void help(void) { //printing out the menu
    printf("SYNOPSIS\n");
    printf("  A Huffman encoder.\n");
    printf("  Compresses a file using the Huffman coding algorithm.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./encode [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -h		 Program usage and help.\n");
    printf("  -v		 Print compression statistics.\n");
    printf("  -i infile	 	 Input file to compress.\n");
    printf("  -o outfile	 Output of compressed data.\n");
    return;
}

int main(int argc, char **argv) {
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    if (outfile != STDOUT_FILENO) {
        close(outfile);
    }
    bool verbose = false;

    //the command lines with switch cases
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

    //creating the histogram
    uint64_t histogram[ALPHABET] = { 0 };
    uint32_t s_symbol = 0;
    uint8_t buffer[BLOCK] = { 0 };
    //Header header = construct_header(infile, outfile);

    histogram[0] += 1; // histogram will have two elements present
    histogram[ALPHABET - 1] += 1; //increment the count element 0 and 255
    //bytes_read = read_bytes(infile, buffer, BLOCK);

    int bytes = 0;
    while ((bytes = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (int i = 0; i < bytes; i += 1) {
            if (histogram[buffer[i]] == 0) {
                s_symbol += 1;
            }
            histogram[buffer[i]] += 1;
        }
    }

    //build the tree
    Node *root = build_tree(histogram); //using build tree to use pq

    Code table[ALPHABET] = { 0 }; //set the table for build codes
    build_codes(root, table);

    //file permissions
    //creating the header
    //this is to initialize the header
    struct stat sbuffer;
    fstat(infile, &sbuffer);
    fchmod(outfile, sbuffer.st_mode);

    Header header = { 0, 0, 0, 0 }; //construct header CITE: Tutor Eric
    header.magic = MAGIC; //set to magic number
    header.permissions = sbuffer.st_mode;
    header.tree_size = (3 * s_symbol) - 1;
    header.file_size = sbuffer.st_size;

    //Calling for my file permissions
    //Header header = construct_header(infile, outfile);

    write_bytes(outfile, (uint8_t *) &header, sizeof(header)); //writing the bytes

    //dump tree (arrangement)
    dump_tree(outfile, root);

    //get the infile stats
    lseek(infile, 0, SEEK_SET); //allows the file offset to be set beyond the end of the file
    //bytes_read = read_bytes(infile, buffer, BLOCK);
    //this is where we will be writing
    bytes = 0;
    while ((bytes = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (int i = 0; i < bytes; i += 1) {
            write_code(outfile, &table[buffer[i]]);
        }
    }
    flush_codes(outfile);

    /*if (verbose == true) {
        //printing stats
        fstat(infile, &sbuffer);
        //fprint the stats
        fprintf(stderr, "Uncompressed file size: %" PRId64 " bytes\n", header.file_size);
        fprintf(
            stderr, "Compressed file size: %" PRId64 "bytes\n", bytes_written - header.file_size);
        // space saving
    }*/

    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}
