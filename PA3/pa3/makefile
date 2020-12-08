CC=g++
CFLAG=-c
DBGFLAGS=-g
OPTFLAGS=-Ofast
STD=-std=c++11

all: bin/cb

debug: bin/cb.dbg bin/cb

bin/cb: src/main.cpp
	$(CC) $(OPTFLAGS) $(STD) $< -o $@

bin/cb.dbg: src/main.cpp
	$(CC) $(DBGFLAGS) $(STD) $< -o $@

clean:
	rm -rf *.o bin/*
