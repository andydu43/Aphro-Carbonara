#!/bin/makefile

CC=gcc

CFLAGS=-Wall -Wextra -ansi -pedantic -Wchar-subscripts -Wdouble-promotion #-Werror -Wcomment -Wformat
LDFLAGS=-lSDL2 -lSDL2_ttf

OBJ=main.o map.o charac.o #display.o engine.o

EXEC=aphroCarbo

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)


main.o: main.c *.h
	$(CC) -c main.c $(CFLAGS)

map.o: map.c map.h charac.h
	$(CC) -c map.c $(CFLAGS)

charac.o: charac.c charac.h
	$(CC) -c charac.c $(CFLAGS)

#display.o: display.c display.h map.h charac.h
#	$(CC) -c display.c $(CFLAGS)

#engine.o: engine.c engine.h charac.h map.h
#	$(CC) -c engine.c $(CFLAGS)

clean:
	rm *.o

cleaner: clean
	rm $(EXEC)