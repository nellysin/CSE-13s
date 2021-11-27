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
