CC = clang
CFLAGS = -g -Wall -Werror -Wextra -Wpedantic

all: banhammer

#LINKING
banhammer: banhammer.o node.o
	$(CC) $(CFLAGS) -o banhammer banhammer.o node.o

#OBJECTS
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f banhammer *.o

format:
	clang-format -i -style=file *[c,h]
