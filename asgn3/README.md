# Assignment 3 - Sorting: Putting your affairs in order

In this assignment, Sorting: Putting your affairs in order, I tested insertion, heap, shell, and quick sort. 
Each sort is tested by a specified command line option by sorting an array of pseudorandom numbers. 
The command line option for -n, -p, and -r are intended to have a user input for the size of the array, how many elements to print,
and generating a seed of their choice. This is also a chance to have an introductory to memory.  

The main point of this assignment is to understand the different sorting algorithms by experimenting through program C.

## Building

Build the program with:

'''
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: sorting

sorting: sorting.o insert.o stats.o shell.o quick.o heap.o
        $(CC) -o sorting sorting.o insert.o stats.o shell.o quick.o heap.o $(LFLAGS)

sorting.o: sorting.c set.h
        $(CC) $(CFLAGS) -c sorting.c

insert.o: insert.c set.h insert.h
        $(CC) $(CFLAGS) -c insert.c

stats.o: stats.c set.h stats.h
        $(CC) $(CFLAGS) -c stats.c

shell.o: shell.c set.h shell.h
        $(CC) $(CFLAGS) -c shell.c

heap.o: heap.c set.h heap.h
        $(CC) $(CFLAGS) -c heap.c

quick.o: quick.c set.h quick.h
        $(CC) $(CFLAGS) -c quick.c
'''

## Running

This program is designed to run on Ubuntu, Linux in C program with:

'''
$./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]
'''

## Bugs

In the shell.c (shell sorting), the moves and compares are different from the resouces shell sort.
(Went to a couple office hours and unable to find a solution)
