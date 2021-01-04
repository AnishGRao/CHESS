
all:
	g++ -O3 piece_utf.h pieces.h chess.cpp -o chess.o; ./chess.o
debug:
	g++ -g a.cpp -o $(shell basename $(CURDIR))_debug.o;

clean:
	rm *.o
