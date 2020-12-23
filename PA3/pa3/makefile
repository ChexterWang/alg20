CC=g++
STD=-std=c++11
obj=main.o solver.o

all: bin/cb

debug: bin/cb.dbg bin/cb

bin/cb: $(obj)
	$(CC) -O3 $(STD) $(obj) -o $@
bin/cb.dbg: $(obj)
	$(CC) -g $(STD) $(obj) -o $@

%.o: src/%.cpp
	$(CC) -c $^ -o $@

clean:
	rm -rf *.o bin/*
