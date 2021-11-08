#include "defines.h"
#include "huffman.h"
#include "header.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "code.h"

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define OPTIONS "hvi:o:"

//CITE: Professor Long for steps of encode in assignment doc (ALL)
//CITE: TA Eugene for pseudo code and structure of encode (ALL) during 11/4 & 11/2 section
//CITE: Tutor Eric for pseudo code of encode during 11/3 (ALL) session
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

struct stat sbuffer;
//a constructor for the header
Header construct_header(int infile, int outfile, uint32_t s_symbols) {
    Header header = { 0, 0, 0, 0 };
    fstat(infile, &sbuffer);
    fchmod(outfile, sbuffer.st_mode);
    header.magic = MAGIC;
    header.permissions = sbuffer.st_mode;
    header.tree_size = (3 * s_symbols) - 1;
    header.file_size = sbuffer.st_size;
    return header;
}

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

    uint64_t uncompressed = 0;
    uint64_t compressed = 0;

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

    histogram[0] += 1; // histogram will have two elements present
    histogram[ALPHABET - 1] += 1; //increment the count element 0 and 255

    while ((bytes_read = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (uint64_t i = 0; i < bytes_read; i += 1) {
            if (histogram[buffer[i]] == 0) {
                s_symbol += 1;
            }
            histogram[buffer[i]] += 1;
        }
    }
    uncompressed = bytes_read;

    //build the tree
    Node *root = build_tree(histogram); //using build tree to use pq

    Code table[ALPHABET] = { 0 }; //set the table for build codes
    build_codes(root, table);

    //Calling for my file permissions and initialize the header
    Header header = construct_header(infile, outfile, s_symbol);

    write_bytes(outfile, (uint8_t *) &header, sizeof(header)); //writing the bytes

    //dump tree (arrangement)
    dump_tree(outfile, root);

    //get the infile stats
    lseek(infile, 0, SEEK_SET); //allows the file offset to be set beyond the end of the file
    //this is where we will be writing
    bytes_read = 0;
    while ((bytes_read = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (uint64_t i = 0; i < bytes_read; i += 1) {
            write_code(outfile, &table[buffer[i]]);
        }
    }
    compressed = bytes_written; //for stats
    flush_codes(outfile); //flush out the codes

    //CITE: Tutor Eric for printing the stats
    fstat(infile, &sbuffer); // printing out the statistics
    double stat
        = 100 * (1 - (((double) bytes_written) - header.file_size) / (double) header.file_size);
    fprintf(stderr, "Uncompressed file size: %" PRId64 " bytes\n", header.file_size);
    fprintf(
        stderr, "Compressed file size: %" PRId64 " bytes\n", (bytes_written - header.file_size));
    fprintf(stderr, "Space saving: %0.2lf%c\n", stat, '%');

    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}
