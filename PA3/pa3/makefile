CC=g++ -std=c++11
obj=main.o solver.o
_obj=_main.o _solver.o

all: bin/cb

d: bin/cb.dbg

bin/cb: $(obj)
	$(CC) -O3 $(obj) -o $@
main.o: src/main.cpp
	$(CC) -O3 -c $^ -o $@
solver.o: src/solver.cpp
	$(CC) -O3 -c $^ -o $@

bin/cb.dbg: $(_obj)
	$(CC) -g $(_obj) -o $@
_main.o: src/main.cpp
	$(CC) -g -c $^ -o $@
_solver.o: src/solver.cpp
	$(CC) -g -c $^ -o $@

c:
	rm -rf *.o bin/* out/*
