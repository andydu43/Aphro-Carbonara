#!/bin/makefile

CC=gcc

CFLAGS=-Wall -Wextra -ansi -pedantic -Wchar-subscripts -Wdouble-promotion #-Werror -Wcomment -Wformat

LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image

OBJ=main.o map.o charac.o evenement.o display.o menu.o

EXEC=aphroCarbo

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

main.o: main.c *.h
	$(CC) -c main.c $(CFLAGS)

map.o: map.c map.h charac.h
	$(CC) -c map.c $(CFLAGS)

charac.o: charac.c charac.h
	$(CC) -c charac.c $(CFLAGS)

display.o: display.c display.h map.h charac.h
	$(CC) -c display.c $(CFLAGS)

evenement.o: evenement.c evenement.h charac.h map.h display.h
	$(CC) -c evenement.c $(CFLAGS)

menu.o: menu.c menu.h
	$(CC) -c menu.c $(CFLAGS)

menu: menu.c
	gcc -o menu menu.c $(CFLAGS) $(LDFLAGS)

clean:
	rm *.o

cleaner: clean
	rm $(EXEC)
