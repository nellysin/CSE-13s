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

%i: %.c
	$(CC) $(CFLAGS) -c $c -o $@

#CLEANING
clean:
	rm -f *o

#FORMATING
format:
	clang-format -i -style=file *.[ch]
