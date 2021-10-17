CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: sorting

sorting: sorting.o insert.o stats.o shell.o quick.o heap.o
	$(CC) -o sorting sorting.o insert.o stats.o shell.o quick.o heap.o $(LFLAGS)

insert: insert.o stats.o
	$(CC) -o insert insert.o stats.o $(LFLAGS)

shell: shell.o stats.o
	$(CC) -o shell shell.o stats.o $(LFLAGS)

heap: heap.o stats.o
	$(CC) -o heap heap.o stats.o $(LFLAGS)

quick: quick.o stats.o
	$(CC) -o quick quick.o stats.o $(LFLAGS)

sorting.o: sorting.c set.h stats.h
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

clean:
	rm -f sorting sorting.o
	rm -f insert insert.o
	rm -f shell shell.o
	rm -f heap heap.o
	rm -f quick quick.o
	rm -f stats stats.o

format:
	clang-format -i -style=file *.[ch]

debug: CFLAGS += -O0 -g

debug: all
