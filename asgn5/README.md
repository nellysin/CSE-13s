# Assignment 5 - Huffman Coding

In this assignment, we are implmenting a Huffman encoder. It will read an input in a text file, and the Huffman encoder will encode the contents.
We will then use the encoded compressed file to decode it. The decoder will read the input file then decompress it -- resetting it back to the pre encoded file. The user must make their own text file first inorder to run the encoder and decoder.
  
## Building

Build the program with:

'''
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: encode decode

encode: encode.o node.o stack.o pq.o io.o huffman.o code.o
        $(CC) -o encode encode.o node.o stack.o pq.o io.o huffman.o code.o

decode: decode.o node.o stack.o pq.o io.o huffman.o code.o
        $(CC) -o decode decode.o node.o stack.o pq.o io.o huffman.o code.o

huffman.o:  huffman.c huffman.h code.h defines.h node.h pq.h io.h stack.h
        $(CC) $(CFLAGS) -c huffman.c

encode.o: encode.c defines.h huffman.h code.h node.h pq.h io.h stack.h header.h
        $(CC) $(CFLAGS) -c encode.c

decode.o: decode.c defines.h huffman.h code.h node.h pq.h io.h stack.h header.h
        $(CC) $(CFLAGS) -c decode.c

node.o: node.c node.h
        $(CC) $(CFLAGS) -c node.c

stack.o: stack.h node.c node.h
        $(CC) $(CFLAGS) -c stack.c

pq.o: pq.c pq.h node.c node.h
        $(CC) $(CFLAGS) -c pq.c

code.o: code.c code.h node.c node.h
        $(CC) $(CFLAGS) -c code.c

io.o: io.c io.h defines.h code.h
        $(CC) $(CFLAGS) -c io.c
'''

## Running

This program is designed to run on Ubuntu, Linux in C program with:

'''
$./encode [-h] [-i infile] [-o outfile]
'''

'''
$./decode [-hvui:o:] [-i infile] [-o outfile]
'''

## Bugs
1.
	I have checked valgrind for my encode and there is no memory leaks (checked with multiple text files), but pipeline says there is.
2.
	My encode works halfway but, not fully.
