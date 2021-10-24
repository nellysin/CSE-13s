# Assignment 4 - The Perambulations of Denver Long

In this assignment we must find the shortest path Denver Long must take. We must implement fake ADTs for graph, stack, and path.
Each we have to use when we read the file for the graph, listing the vertices, city names, and the starting and the possible ending 
point including the length it takes from one to another. The main part of this assignment was to implement a DFS, depth for search,
this is the part to determine the shortest path. Denver will be visiting each of the city and will only visit there once but will 
end up where he started, this is called the hamiltonian path. If the city has not been visited but it's reachable, Denver should visit.

## Building

Build the program with:

'''
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: tsp

tsp: tsp.o path.o graph.o stack.o
        $(CC) -o tsp tsp.o path.o graph.o stack.o $(LFLAGS)

path: path.o graph.o stack.o
        $(CC) -o path path.o graph.o stack.o $(LFLAGS)

tsp.o: tsp.c graph.h stack.h path.h
        $(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c graph.h
        $(CC) $(CFLAGS) -c graph.c

stack.o: stack.c stack.h
        $(CC) $(CFLAGS) -c stack.c

path.o: path.c path.h graph.h stack.h
        $(CC) $(CFLAGS) -c path.c
'''

## Running

This program is designed to run on Ubuntu, Linux in C program with:

'''
$./tsp [-hvui:o:] [-i infile] [-o outfile]
'''

## Bugs


