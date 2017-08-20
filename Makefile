#!/bin/makefile

OFILES=main.o moteur.o
EXEC=first_window

LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image
CFLAGS=-Wall -Wextra -ansi -pedantic -Wextra -Wchar-subscripts -Wdouble-promotion -Werror -Wcomment -Wformat

CC=gcc

CLEAN=*.o *~

all:$(EXEC)

$(EXEC):$(OFILES)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm $(CLEAN)
clear: clean

cleaner:
	rm $(EXEC) $(CLEAN)
