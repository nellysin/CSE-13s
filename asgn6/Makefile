CC = clang
CFLAGS = -g -Wall -Werror -Wextra -Wpedantic $(shell pkg-config -- cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: encrypt decrypt keygen

#LINKING
keygen: keygen.o numtheory.o randstate.o rsa.o
	$(CC) $(CFLAGS) -o keygen keygen.o numtheory.o randstate.o rsa.o $(CFLAGS)

encrypt: encrypt.o numtheory.o randstate.o
	$(CC) $(CFLAGS) -o encrypt encrypt.o numtheory.o randstate.o rsa.o $(CFLAGS)

decrypt: decrypt.o numtheory.o randstate.o
	$(CC) $(CFLAGS) -o decrypt decrypt.o numtheory.o randstate.o rsa.o $(CFLAGS)

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

decript.o: decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAGS) -c randstate.c

numtheory.o: numtheory.c numtheory.h
	$(CC) $(CFLAGS) -c numtheory.c

rsa.o: rsa.c rsa.h
	$(CC) $(CFLAGS) -c rsa.c

#CLEANING
clean:
	rm -f *o

#FORMATING
format:
	clang-format -i -style=file *.[ch]
