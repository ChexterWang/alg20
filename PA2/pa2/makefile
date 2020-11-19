CC=g++
CFLAG=-c
DBGFLAGS=-g
OPTFLAGS=-Ofast
STD=-std=c++11

all: bin/mps bin/mps.dbg

bin/mps: src/main.cpp
	$(CC) $(OPTFLAGS) $(STD) $< -o $@
bin/mps.dbg: src/main.cpp
	$(CC) $(DBGFLAGS) $(STD) $< -o $@

clean:
	rm -rf *.o bin/*
