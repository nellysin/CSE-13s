CC = clang
CFLAGS = -g -Wall -Wpedantic -Werror -Wextra
LFLAGS = `pkg-config --libs gmp`

all: encrypt decrypt keygen

#LINKING
keygen: keygen.o
	$(CC) $(CFLAGS) -o keygen keygen.c $(CFLAGS)

encrypt: encrypt.o
	$(CC) $(CFLAGS) -o encrypt encrypt.c $(CFLAGS)

decrypt: decrypt.o
	$(CC) $(CFLAGS) -o decrypt decrypt.c $(CFLAGS)

%i: %.c
	$(CC) $(CFLAGS) -c $c -o $@

#CLEANING
clean:
	rm -f *o

#FORMATING
format:
	clang-format -i -style=file *.[ch]
