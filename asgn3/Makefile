C = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: sorting

debug: all

debug: CFLAGS += -g

sorting: sorting.o insert.o stats.o
	$(CC) -o sorting sorting.o insert.o stats.o $(LFLAGS)

insert: insert.o stats.o
	$(CC) -o insert insert.o stats.o $(LFLAGS)

shell: shell.o stats.o
	$(CC) -o shell shell.o stats.o $(LFLAGS)

sorting.o: sorting.c insert.h set.h stats.h
	$(CC) $(CFLAGS) -c sorting.c

insert.o: insert.c insert.h set.h stats.h
	$(CC) $(CFLAGS) -c insert.c

stats.o: stats.c stats.h 
	$(CC) $(CFLAGS) -c stats.c

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

clean:
	rm -f sorting sorting.o
	rm -f insert insert.o

format:
	clang-format -i style=file *.[ch]
