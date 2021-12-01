# Assignment 7 - The Great Firewall of Santa Cruz: Bloom Filters, Binary Trees, and Hash Tables

In this assignment we are helping the leader of the Glorious People's Republic of Santa Cruz to filter out words in the internet used by their citizens.
Any word that is used as hurtful or offensive must be detected and alert the usage of them to the citizens.
If they are cause using bad words, a message will be sent to them indicating that they are using the badwords along with the words they used. 
If they were caught using both bad and good words, they will still be warned but they will be praised for using good words. Again, it will show their efforts of using good words and the bad words that are discouraged.
Lastly, there will be a message to praise citizens who use good words.

## Building
```
CC = clang
CFLAGS = -g -Wall -Werror -Wextra -Wpedantic
LFLAGS = -lm

all: banhammer

#LINKING
banhammer: banhammer.o node.o bv.o bf.o speck.o bst.o ht.o parser.o
        $(CC) $(CFLAGS) -o banhammer banhammer.o node.o bv.o bf.o speck.o bst.o ht.o parser.o $(LFLAGS)

#OBJECTS
%.o: %.c
        $(CC) $(CFLAGS) -c $< -o $@

clean:
        rm -f banhammer *.o

format:
        clang-format -i -style=file *[c,h]
```

## Running
This program is intended to run on Ubuntu, Linux in C program with:

```
./banhammer [-hs] [-t size] [-f size]
```

# Bugs
Currently, there are no known bugs my submitted program.
