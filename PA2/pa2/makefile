CC=g++
CFLAG=-c
DBGFLAGS=-g
OPTFLAGS=-O2

all: bin/mps bin/mps.dbg

bin/mps: src/main.cpp
	$(CC) $(OPTFLAGS) $< -o $@
	termux-elf-cleaner bin/mps
bin/mps.dbg: src/main.cpp
	$(CC) $(DBGFLAGS) $< -o $@
	termux-elf-cleaner bin/mps.dbg

clean:
	rm -rf log *.o bin/*
