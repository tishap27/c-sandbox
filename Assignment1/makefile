CC=gcc
CFLAGS=-Wall -Wextra -ansi -pedantic

all: treasure_hunt

treasure_hunt: treasure_hunt.o
	$(CC) $(CFLAGS) -o $@ $^

treasure_hunt.o: treasure_hunt.c Treasure_hunt.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o treasure_hunt

run: all
	./treasure_hunt