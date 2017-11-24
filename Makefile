CC=gcc
CFLAGS=-Wall -O3 -std=c99 -pedantic -lncurses
DIRBUILD=build
DIRSRC=src
SOURCES=$(shell ls $(DIRSRC)/*.c)
EXECUTABLE=$(DIRBUILD)/cue

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	mkdir -p $(DIRBUILD)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)

.PHONY: clean all $(DIRSRC)/main.c
